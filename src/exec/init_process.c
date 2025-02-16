/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:20:03 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 19:19:09 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fds(t_exp *exp)
{
	if (exp->infd != STDIN_FILENO)
	{
		close(exp->infd);
		exp->infd = STDIN_FILENO;
	}
	if (exp->outfd != STDOUT_FILENO)
	{
		close(exp->outfd);
		exp->outfd = STDOUT_FILENO;
	}
}

static void	wait_child(int pid, t_status *status)
{
	int	exit_status;

	ignore_sigint();
	waitpid(pid, &exit_status, 0);
	set_sigint();
	dbg_number("child process finished with exit status ", exit_status);
	if (WIFEXITED(exit_status))
		*status = WEXITSTATUS(exit_status);
	else
		*status = 128 + WTERMSIG(exit_status);
}

int	init_process(t_exp *exp, t_status *status, char ***envp, t_runner runner)
{
	int		exit_status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), EX_ERR);
	if (pid == 0)
	{
		if (exp->infd != STDIN_FILENO)
			dup2(exp->infd, STDIN_FILENO);
		if (exp->outfd != STDOUT_FILENO)
			dup2(exp->outfd, STDOUT_FILENO);
		exit_status = runner(exp->argc, exp->argv, envp);
		dbg_number("runner finished with exit status ", exit_status);
		close_fds(exp);
		return (*status);
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
	if (execve(argv[0], argv, *envp) == -1)
	{
		perror("execve");
		return (EX_ERR);
	}
	return (EX_OK);
}
