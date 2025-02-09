/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:57:22 by adelille          #+#    #+#             */
/*   Updated: 2024/12/15 22:53:02 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

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
