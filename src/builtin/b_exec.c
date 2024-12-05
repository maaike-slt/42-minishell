/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:53:33 by msloot            #+#    #+#             */
/*   Updated: 2024/12/02 22:00:58 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(t_args *arg)
{
	if (ft_strcmp(arg->argv[0], "echo") == 0)
		return (echo(arg));
	if (ft_strcmp(arg->argv[0], "cd") == 0)
		return (cd(arg));
	if (ft_strcmp(arg->argv[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(arg->argv[0], "env") == 0)
		return (env(arg->envp));
	else
		return (-1);
}