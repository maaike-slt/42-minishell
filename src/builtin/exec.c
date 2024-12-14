/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:53:33 by msloot            #+#    #+#             */
/*   Updated: 2024/12/14 18:47:04 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(int argc, char **argv, char ***envp)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (echo(argc, argv));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argc, argv, *envp));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(argv[0], "env") == 0)
		return (env(*envp));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (unset(argc, argv, *envp));
	if (ft_strcmp(argv[0], "export") == 0)
		return (export(argc, argv, envp));
	else
		return (-1);
}
