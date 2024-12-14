/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:12:00 by adelille          #+#    #+#             */
/*   Updated: 2024/12/14 18:41:54 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	loop(char ***envp)
{
	char		*line;
	t_exp_list	*exp_list;
	t_exp_list	*current;
	t_dispatch	dispatch_ret;

	while (true)
	{
		line = prompt();
		if (!line)
			continue ;
		dbg(line);
		exp_list = parse(line, *envp);
		free(line);
		current = exp_list;
		while (current)
		{
			dispatch_ret = dispatch(current->content, envp);
			if (dispatch_ret == D_EXIT)
				return (ft_lstclear((t_list **)&exp_list, exp_free), true);
			current = current->next;
		}
		ft_lstclear((t_list **)&exp_list, exp_free);
	}
	return (true);
}
