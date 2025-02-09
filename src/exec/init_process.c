/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:20:03 by adelille          #+#    #+#             */
/*   Updated: 2025/02/09 16:30:38 by adelille         ###   ########.fr       */
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

int	init_process(t_exp *exp, char ***envp, t_runner runner)
{
	pid_t	pid;
	int		exit_code;

	// FIXME: must not fork when is_builtin && infd == STDIN_FILENO && outfd == STDOUT_FILENO
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EX_ERR);
	if (pid == 0)
	{
		if (exp->infd != STDIN_FILENO)
			dup2(exp->infd, STDIN_FILENO);
		if (exp->outfd != STDOUT_FILENO)
			dup2(exp->outfd, STDOUT_FILENO);
		exit_code = runner(exp->argc, exp->argv, envp);
		dbg("runner finished");
		close_fds(exp);
		exp_free((void *)exp);
		exit(exit_code);
	}
	close_fds(exp);
	waitpid(pid, NULL, 0);
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
