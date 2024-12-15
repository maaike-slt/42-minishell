/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:57:22 by adelille          #+#    #+#             */
/*   Updated: 2024/12/15 19:12:57 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static bool	extract_string(char *ret, const char *line, size_t *i, char **envp)
{
	if (line[*i] == '\'')
		ret = ft_strjoin_free(ret,
				extract_single_quote(line, i), true, true);
	else if (line[*i] == '"')
		ret = ft_strjoin_free(ret,
				extract_double_quote(line, i, envp), true, true);
	else if (line[*i] == '\\')
	{
		(*i)++;
		ft_strpush(&ret, line[*i]);
	}
	else if (line[*i] == '$')
		ret = ft_strjoin_free(ret,
				extract_variable(line, i, envp), true, true);
	else
		return (false)
	return (true);
}
