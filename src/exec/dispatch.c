/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:23:35 by msloot            #+#    #+#             */
/*   Updated: 2025/02/02 17:08:35 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tmp

static int	i_fork(const t_exp *exp, char **envp)
{
	char	*path;
	pid_t	pid;

	path = find_bin_path(exp->argv[0], envp);
	if (path == NULL)
		return (free(path), error(exp->argv[0], "command not found"),
			EX_NOTFOUND);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EX_ERR);
	if (pid == 0)
	{
		if (execve(path, exp->argv, envp) == -1)
			perror("execve");
		sleep(1);
		free(path);
		exit(0);	// FIXME: do not just exit(0)
	}
	waitpid(pid, NULL, 0);
	free(path);
	return (EX_OK);
}

t_dispatch	dispatch(const t_exp *exp, char ***envp)
{
	if (ft_strcmp(exp->argv[0], "exit") == 0)
	{
		dbg("👋");
		return (D_EXIT);
	}
	else
		if (!builtin(exp->argc, exp->argv, envp))
			return (D_ERROR);
	// else if  in path
	// for testing
	else if (true)
		i_fork(exp, *envp);
	else
		ft_putstr("command not found"); // TODO: finish this branch
	return (D_OKAY);
}
