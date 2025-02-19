/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:57:22 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 18:47:19 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

bool	extract_string(char **ret, const char *line, size_t *i, t_env *e)
{
	if (line[*i] == '\'')
		*ret = ft_strjoin_free(*ret,
				extract_single_quote(line, i), true, true);
	else if (line[*i] == '"')
		*ret = ft_strjoin_free(*ret,
				extract_double_quote(line, i, e), true, true);
	else if (line[*i] == '\\')
	{
		(*i)++;
		ft_strpush(ret, line[*i]);
	}
	else if (line[*i] == '$')
		*ret = ft_strjoin_free(*ret,
				extract_variable(line, i, e), true, true);
	else
		return (false);
	return (true);
}
