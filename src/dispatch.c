/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:23:35 by msloot            #+#    #+#             */
/*   Updated: 2024/12/09 21:30:22 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tmp
static int	i_fork(const t_exp *exp, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), EX_ERR);
	if (pid == 0)
	{
		if (execve("/usr/bin/ls", exp->argv, envp) == -1)
			perror("execve");
		ft_putstr("child\n");
		sleep(1);
		exit(0);	// FIXME: do not just exit(0)
	}
	ft_putstr("parent\n");
	waitpid(pid, NULL, 0);
	ft_putstr("child is done, too much child labor\n");
	return (EX_OK);
}

t_dispatch	dispatch(const t_exp *exp, char **envp)
{
	if (ft_strcmp(exp->argv[0], "exit") == 0)
	{
		printf("\033[1;36m[DEBUG]\033[0m\texiting\n");
		return (D_EXIT);
	}
	else
		if (!builtin(exp->argc, exp->argv, envp))
			return (D_ERROR);
	// else if  in path
	// for testing
	else if (true)
		i_fork(exp, envp);
	else
		ft_putstr("command not found"); // TODO: finish this branch
	return (D_OKAY);
}
