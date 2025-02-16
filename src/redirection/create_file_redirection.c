/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:11:37 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 13:49:07 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shift_argv(t_exp *exp, size_t i)
{
	while (exp->argv[i])
	{
		exp->argv[i] = exp->argv[i + 1];
		i++;
	}
	exp->argc -= 1;
}

static bool	close_existing(t_exp *exp, char ir)
{
	if ((ir == IR_FILE_OUT || ir == IR_FILE_OUT_APPEND)
		&& exp->outfd > STDERR_FILENO)
	{
		if (close(exp->outfd) == -1)
			return (perror("close"), false);
	}
	else if ((ir == IR_FILE_IN || ir == IR_HEREDOC)
		&& exp->infd > STDERR_FILENO)
	{
		if (close(exp->infd) == -1)
			return (perror("close"), false);
	}
	return (true);
}

static bool	handle_redirection(t_exp *exp, size_t i)
{
	char	ir;

	ir = exp->argv[i][0];
	if (!close_existing(exp, ir))
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
		dbg("heredoc not implemented yet");
		exit(42);
	}
	if (exp->outfd == -1 || exp->infd == -1)
		return (perror("open"), false);
	free(exp->argv[i]);
	free(exp->argv[i + 1]);
	shift_argv(exp, i);
	shift_argv(exp, i);
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
