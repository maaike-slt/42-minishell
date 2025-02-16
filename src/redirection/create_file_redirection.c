/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:11:37 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 13:13:51 by adelille         ###   ########.fr       */
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

static bool	create_single_exp_file_redirection(t_exp *exp)
{
	size_t	i;

	i = 0;
	while (i < (size_t)exp->argc)
	{
		if (exp->argv[i][0] == IR_FILE_OUT)
		{
			if (exp->outfd > STDERR_FILENO)
				close(exp->outfd);
			exp->outfd = open(exp->argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			free(exp->argv[i]);
			free(exp->argv[i + 1]);
			shift_argv(exp, i);
			shift_argv(exp, i);
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
