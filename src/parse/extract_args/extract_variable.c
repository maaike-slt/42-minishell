/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:11 by adelille          #+#    #+#             */
/*   Updated: 2025/02/23 17:29:47 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

bool	is_variable_sep(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

char	*get_special_variable(const char *line, size_t *i, size_t start)
{
	char	*ret;

	if (line[*i] == '?')
	{
		ret = ft_strdup("s?e");
		if (!ret)
			return (error("malloc", strerror(errno)), NULL);
		ret[0] = INTERNAL_VAR_START;
		ret[2] = INTERNAL_VAR_END;
		return (ret);
	}
	else if (line[start - 1] == '{')
	{
		while (line[*i] && line[*i] != '}')
			(*i)++;
		ret = ft_strndup(&line[start - 2], *i - start + 3);
		error(ret, "bad substitution");
		free(ret);
		return (NULL);
	}
	ret = ft_strndup(&line[start - 1], *i - start + 2);
	if (!ret)
		return (error("malloc", strerror(errno)), NULL);
	return (ret);
}

char	*mark_variable(const char *line, size_t *i)
{
	char	*key;
	char	*ret;
	size_t	start;

	(*i)++;
	if (line[*i] == '{')
		i++;
	start = *i;
	while (line[*i] && !is_variable_sep(line[*i]))
		i++;
	key = ft_strndup(&line[start], *i - start);
	if (!key)
		return (error("malloc", strerror(errno)), NULL);
	if (key[0] == '\0')
		return (free(key), get_special_variable(line, i, start));
	ft_strpush(&ret, INTERNAL_VAR_START);
	if (!ret)
		return (error("malloc", strerror(errno)), NULL);
	ret = ft_strjoin_free(ret, key, true, true);
	if (!ret)
		return (error("malloc", strerror(errno)), NULL);
	ft_strpush(&ret, INTERNAL_VAR_END);
	if (!ret)
		return (error("malloc", strerror(errno)), NULL);
	return (ret);
}
