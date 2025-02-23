/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:57:22 by adelille          #+#    #+#             */
/*   Updated: 2025/02/23 14:01:04 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

void	set_redirection_fd(t_exp *exp, char *arg)
{
	if (arg[0] == IR_FILE_IN || arg[0] == IR_HEREDOC)
		exp->infd = arg[0];
	if (arg[0] == IR_FILE_OUT || arg[0] == IR_FILE_OUT_APPEND)
		exp->outfd = arg[0];
}

bool	extract_redirection(char **ret, const char *line, size_t *i)
{
	if (*ret[0] == '\0' && line[*i] == '<')
	{
		if (line[*i + 1] == '<')
		{
			ft_strpush(ret, IR_HEREDOC);
			(*i)++;
		}
		else
			ft_strpush(ret, IR_FILE_IN);
		(*i)++;
	}
	else if (*ret[0] == '\0' && line[*i] == '>')
	{
		if (line[*i + 1] == '>')
		{
			ft_strpush(ret, IR_FILE_OUT_APPEND);
			(*i)++;
		}
		else
			ft_strpush(ret, IR_FILE_OUT);
		(*i)++;
	}
	else
		return (false);
	return (true);
}
