/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:20:03 by adelille          #+#    #+#             */
/*   Updated: 2025/02/26 21:24:14 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_exp *exp)
{
	if (exp->infd > STDERR_FILENO)
	{
		close(exp->infd);
		exp->infd = STDIN_FILENO;
	}
	if (exp->outfd > STDERR_FILENO)
	{
		close(exp->outfd);
		exp->outfd = STDOUT_FILENO;
	}
}

static void	wait_child(int pid, t_status *status)
{
	int	exit_status;

	set_sigint(&process_handler);
	waitpid(pid, &exit_status, 0);
	set_sigint(&prompt_handler);
	dbg_number("child process finished with exit status ", exit_status);
	if (WIFEXITED(exit_status))
		*status = WEXITSTATUS(exit_status);
	else
		*status = 128 + WTERMSIG(exit_status);
}

int	init_process(t_exp *exp, t_status *status, char ***envp, t_runner runner)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (error("fork", strerror(errno)), EX_ERR);
	if (pid == 0)
	{
		if (exp->infd != STDIN_FILENO)
			dup2(exp->infd, STDIN_FILENO);
		if (exp->outfd != STDOUT_FILENO)
			dup2(exp->outfd, STDOUT_FILENO);
		*status = runner(exp->argc, exp->argv, envp);
		dbg_number("runner finished with exit status ", *status);
		close_fds(exp);
		return (EX_CHILD);
	}
	close_fds(exp);
	wait_child(pid, status);
	return (EX_OK);
}

int	run_builtin(int argc, char **argv, char ***envp)
{
	return (builtin(argc, argv, envp));
}

int	run_bin(int argc, char **argv, char ***envp)
{
	(void)argc;
	set_sigquit(SIG_DFL);
	if (execve(argv[0], argv, *envp) == -1)
	{
		error("execve", strerror(errno));
		return (EX_ERR);
	}
	return (EX_OK);
}
