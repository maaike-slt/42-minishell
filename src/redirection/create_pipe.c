/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:11:37 by adelille          #+#    #+#             */
/*   Updated: 2025/02/09 17:11:44 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_pipe(t_exp_list *exp_list)
{
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
