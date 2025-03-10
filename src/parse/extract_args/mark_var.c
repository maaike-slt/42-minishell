/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:11 by adelille          #+#    #+#             */
/*   Updated: 2025/02/26 17:10:49 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

bool	is_var_sep(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

static char	*get_special_var(const char *line, size_t *i, size_t start)
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
	ret = ft_strndup(&line[start - 1], *i - start + 1);
	if (!ret)
		return (error("malloc", strerror(errno)), NULL);
	return (ret);
}

static char	*extract_key(const char *line, size_t *i, size_t start)
{
	char	*key;
	char	*ret;

	key = ft_strndup(&line[start], *i - start);
	if (!key)
		return (error("malloc", strerror(errno)), NULL);
	if (key[0] == '\0')
		return (free(key), get_special_var(line, i, start));
	ret = ft_strpush(NULL, INTERNAL_VAR_START);
	if (!ret)
		return (free(key), error("malloc", strerror(errno)), NULL);
	ret = ft_strjoin_free(ret, key, true, true);
	if (!ret)
		return (error("malloc", strerror(errno)), NULL);
	ft_strpush(&ret, INTERNAL_VAR_END);
	if (!ret)
		return (error("malloc", strerror(errno)), NULL);
	return (ret);
}

char	*mark_var(const char *line, size_t *i)
{
	char	*ret;
	size_t	start;
	bool	is_curly;

	(*i)++;
	is_curly = false;
	if (line[*i] == '{')
	{
		is_curly = true;
		(*i)++;
	}
	start = *i;
	while (line[*i] && !is_var_sep(line[*i]))
		(*i)++;
	ret = extract_key(line, i, start);
	if (!ret)
		return (NULL);
	if (!((is_curly && line[*i] == '}')
			|| (ret[0] && ret[1] == '?' && line[*i] == '?')))
		(*i)--;
	if (is_curly && line[*i] == '?')
		(*i)++;
	return (ret);
}
