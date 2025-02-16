/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:11:37 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 12:39:24 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	create_single_exp_file_redirection(t_exp *exp)
{
	int	fd;

	if (exp->out_type == e_none)
		return (true);
	if (exp->out_type == e_truncate)
		fd = open(exp->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (exp->out_type == e_append)
		fd = open(exp->out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(exp->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (false);
	}
	exp->outfd = fd;
	return (true);
}

bool	create_file_redirection(t_exp_list *exp_list)
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
