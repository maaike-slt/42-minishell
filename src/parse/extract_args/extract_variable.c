/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:11 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 18:54:54 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static bool	is_variable_separator(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

char	*get_special_variable(
	const char *line, size_t *i, size_t start, t_env *e)
{
	char	*ret;

	if (line[*i] == '?')
		ret = ft_untoa(*(e->status));
	else if (line[start - 1] == '{')
	{
		while (line[*i] && line[*i] != '}')
			(*i)++;
		ret = ft_strndup(&line[start - 2], *i - start + 3);
		error(ret, "bad substitution");
		free(ret);
		return (NULL);
	}
	else
		ret = ft_strndup(&line[start - 1], *i - start + 2);
	return (ret);
}

char	*extract_variable(const char *line, size_t *i, t_env *e)
{
	char	*key;
	char	*val;
	size_t	start;

	(*i)++;
	if (line[*i] == '{')
		(*i)++;
	start = *i;
	while (line[*i] && !is_variable_separator(line[*i]))
		(*i)++;
	key = ft_strndup(&line[start], *i - start);
	if (!key)
		return (NULL);
	if (key[0] == '\0')
		return (free(key), get_special_variable(line, i, start, e));
	if (line[*i] && is_variable_separator(line[*i]) && line[*i] != '}')
		(*i)--;
	val = ft_getenv(e->envp, key);
	free(key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

#ifdef TEST

static bool	test_var(
	const char *line,
	size_t expected_i,
	const char *expected_remaining,
	const char *expected_ret)
{
	t_status	status;
	char		**envp;
	char		*ret;
	size_t		i;
	bool		r;

	r = EX_OK;
	envp = dummy_envp("VAR=Hello");
	status = 42;
	i = 0;
	ret = extract_variable(line, &i, &(t_env){&status, envp});
	r |= assert_eq("extract variable index", i, expected_i);
	r |= assert_str_eq("extract variable remaining", &line[i],
			expected_remaining);
	r |= (ret == NULL && expected_ret == NULL)
		|| assert_str_eq("extract variable", ret, expected_ret);
	free(ret);
	free(envp);
	return (r);
}

bool	test_extract_variable(void)
{
	bool	r;

	r = EX_OK;
	r |= test_var("$VAR yo", 3, "R yo", "Hello");
	r |= test_var("${VAR}yo", 5, "}yo", "Hello");
	r |= test_var("$VARR yo", 4, "R yo", "");
	r |= test_var("$? yo", 1, "? yo", "42");
	return (r);
}
/* r |= test_var("${=} yo", 3, "} yo", NULL); */

#endif
