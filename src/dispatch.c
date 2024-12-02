/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:23:35 by msloot            #+#    #+#             */
/*   Updated: 2024/12/02 22:26:27 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// tmp
static int	i_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), EX_ERR);
	if (pid == 0)
	{
		ft_putstr("child\n");
		sleep(1);
		exit(0);	// FIXME: do not just exit(0)
	}
	else	// TODO: remove else branch if child quits
	{
		ft_putstr("parent\n");
		waitpid(pid, NULL, 0);
		ft_putstr("child is done, too much child labor\n");
	}
	return (EX_OK);
}

t_dispatch	dispatch(t_args *arg)
{
	if (ft_strcmp(arg->argv[0], "exit") == 0)
	{
		printf("\033[1;36m[DEBUG]\033[0m\texiting\n");
		return (D_EXIT);
	}
	else
		if (!builtin(arg))
			return (D_ERROR);
	// else if  in path
	// for testing
	else if (true)
		i_fork();
	else
		ft_putstr("command not found"); // TODO: finish this branch
	return (D_OKAY);
}