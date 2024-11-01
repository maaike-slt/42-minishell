/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:53:33 by msloot            #+#    #+#             */
/*   Updated: 2024/11/01 15:19:51 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(int argc, char **argv, char **envp)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (echo(argc, argv, envp));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (cd(argc, argv, envp));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd());
	else
		return (-1);
}
