/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:12:00 by adelille          #+#    #+#             */
/*   Updated: 2024/12/08 18:39:04 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	loop(char **envp)
{
	char				*line;
	t_expression_list	*expression_list;
	t_expression_list	*current;
	t_dispatch			dispatch_ret;

	while (true)
	{
		line = prompt();
		if (!line)
			continue ;
		printf("\033[1;36m[DEBUG]\033[0m\tgot: '%s'\n", line);
		expression_list = parse(line, envp);
		free(line);
		current = expression_list;
		while (current)
		{
			dispatch_ret = dispatch(current->content, envp);
			if (dispatch_ret == D_EXIT)
				return (ft_lstclear((t_list **)&expression_list, expression_free), true);
			current = current->next;
		}
		ft_lstclear((t_list **)&expression_list, expression_free);
	}
	return (true);
}
