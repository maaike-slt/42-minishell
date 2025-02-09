/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:23:35 by msloot            #+#    #+#             */
/*   Updated: 2025/02/09 17:06:20 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dispatch	dispatch(t_exp *exp, char ***envp)
{
	if (ft_strcmp(exp->argv[0], "exit") == 0)
	{
		dbg("👋");
		return (D_EXIT);
	}
	else if (is_builtin(exp->argv[0]))
	{
		if (exp->infd == STDIN_FILENO && exp->outfd == STDOUT_FILENO)
		{
			builtin(exp->argc, exp->argv, envp);
			return (D_OKAY);
		}
		if (init_process(exp, envp, run_builtin) == EX_CHILD)
			return (D_EXIT);
	}
	else
	{
		if (!prepare_bin(exp, *envp))
			return (D_OKAY);
		if (init_process(exp, envp, run_bin) == EX_CHILD)
			return (D_EXIT);
	}
	return (D_OKAY);
}
