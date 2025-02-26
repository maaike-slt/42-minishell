/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:11:37 by adelille          #+#    #+#             */
/*   Updated: 2025/02/26 18:47:34 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_argv(t_exp *exp, size_t i)
{
	free(exp->argv[i]);
	while (i < (size_t)exp->argc)
	{
		exp->argv[i] = exp->argv[i + 1];
		i++;
	}
	exp->argc--;
}

static void	handle_fd_error(t_exp *exp)
{
	if (exp->outfd == -1)
	{
		error("open", strerror(errno));
		exp->outfd = STDERR_FILENO;
	}
	if (exp->infd == -1)
	{
		error("open", strerror(errno));
		exp->infd = STDIN_FILENO;
	}
}

static bool	handle_redirection(t_exp *exp, size_t i)
{
	char	ir;

	ir = exp->argv[i][0];
	if (!close_existing_redirection(exp, ir))
		return (false);
	if (ir == IR_FILE_OUT)
		exp->outfd = open(exp->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ir == IR_FILE_OUT_APPEND)
		exp->outfd = open(exp->argv[i + 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ir == IR_FILE_IN)
		exp->infd = open(exp->argv[i + 1], O_RDONLY);
	else if (ir == IR_HEREDOC)
	{
		if (!heredoc(exp))
			return (false);
	}
	handle_fd_error(exp);
	delete_argv(exp, i);
	delete_argv(exp, i);
	return (true);
}

static bool	create_single_exp_file_redirection(t_exp *exp)
{
	size_t	i;

	i = 0;
	while (i < (size_t)exp->argc)
	{
		if (exp->argv[i][0] == IR_FILE_OUT
			|| exp->argv[i][0] == IR_FILE_OUT_APPEND
			|| exp->argv[i][0] == IR_FILE_IN
			|| exp->argv[i][0] == IR_HEREDOC)
		{
			if (!handle_redirection(exp, i))
				return (false);
		}
		else
			i++;
	}
	return (true);
}

bool	create_file_redirection(t_exp_list *exp_list)
{
	t_exp_list	*current;

	current = exp_list;
	while (current)
	{
		if (!create_single_exp_file_redirection(current->content))
			return (false);
		current = current->next;
	}
	return (true);
}
