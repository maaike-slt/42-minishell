/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:13:50 by adelille          #+#    #+#             */
/*   Updated: 2025/02/23 14:05:59 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	exec_all_exp(t_exp_list *exp_list, t_status *status, char ***envp)
{
	t_exp_list	*current;
	t_dispatch	dispatch_ret;

	current = exp_list;
	while (current)
	{
		if (!apply_special_var(current->content, status))
			return (false);
		dispatch_ret = dispatch(current->content, status, envp);
		if (dispatch_ret == D_EXIT)
			return (false);
		current = current->next;
	}
	return (true);
}
