/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:23:35 by msloot            #+#    #+#             */
/*   Updated: 2025/02/23 19:05:19 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dispatch	dispatch(t_exp *exp, t_status *status, char ***envp)
{
	if (exp->argc == 0)
	{
		*status = 0;
		return (close_fds(exp), D_OKAY);
	}
	if (ft_strcmp(exp->argv[0], "exit") == 0)
		return (ft_exit(exp, status));
	else if (is_builtin(exp->argv[0]))
	{
		if (exp->infd == STDIN_FILENO && exp->outfd == STDOUT_FILENO)
		{
			*status = builtin(exp->argc, exp->argv, envp);
			return (D_OKAY);
		}
		if (init_process(exp, status, envp, run_builtin) == EX_CHILD)
			return (D_EXIT);
	}
	else
	{
		if (!prepare_bin(exp, status, *envp))
			return (D_OKAY);
		if (init_process(exp, status, envp, run_bin) == EX_CHILD)
			return (D_EXIT);
	}
	return (D_OKAY);
}
