/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:12:00 by adelille          #+#    #+#             */
/*   Updated: 2025/02/09 14:22:22 by adelille         ###   ########.fr       */
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
		line = prompt(*envp);
		if (!line)
			continue ;
		dbg(line);
		exp_list = parse(line, *envp);
		free(line);
		if (!create_pipe(exp_list))
		{
			ft_lstclear((t_list **)&exp_list, exp_free);
			continue ;
		}
		// TODO: move dispatching to another file
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

bool	create_pipe(t_exp_list *exp_list)
{
	// TODO: move to another file
	int			pipefd[2];
	t_exp_list	*current;

	current = exp_list;
	while (current)
	{
		if (current->content->infd == INTERNAL_PIPE_FD)
			current->content->infd = pipefd[0];
		if (current->content->outfd == INTERNAL_PIPE_FD)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				return (false);
			}
			current->content->outfd = pipefd[1];
		}
		current = current->next;
	}
	return (true);
}
