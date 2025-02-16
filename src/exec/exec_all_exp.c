/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:13:50 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 19:01:32 by adelille         ###   ########.fr       */
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
		dispatch_ret = dispatch(current->content, status, envp);
		if (dispatch_ret == D_EXIT)
			return (false);
		current = current->next;
	}
	return (true);
}
