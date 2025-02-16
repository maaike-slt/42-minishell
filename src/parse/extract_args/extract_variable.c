/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:11 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 16:39:04 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_variable_separator(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

char	*extract_variable(const char *line, size_t *i, char **envp)
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
	if (line[*i] == '}')
		(*i)++;
	if (line[*i] && is_variable_separator(line[*i]))
		(*i)--;
	val = ft_getenv(envp, key);
	free(key);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

#ifdef TEST

static bool	test_extract_variable_does_not_exist(void)
{
	char	**envp;
	char	line[99];
	char	*ret;
	size_t	i;
	bool	r;

	r = EX_OK;
	envp = dummy_envp("VAR=Hello");
	i = 0;
	ft_strlcpy(line, "$VARR yo", 99);
	ret = extract_variable(line, &i, envp);
	r |= assert_eq("extract variable $VARR index", i, 4);
	r |= assert_str_eq("extract variable remaining", &line[i], "R yo");
	r |= assert_str_eq("extract variable $VARR without envp", ret, "");
	free(ret);
	free(envp);
	return (r);
}

bool	test_extract_variable(void)
{
	char	**envp;
	char	line[99];
	char	*ret;
	size_t	i;
	bool	r;

	r = EX_OK;
	envp = dummy_envp("VAR=Hello");
	i = 0;
	ft_strlcpy(line, "$VAR yo", 99);
	ret = extract_variable(line, &i, envp);
	r |= assert_eq("extract variable $VAR index", i, 3);
	r |= assert_str_eq("extract variable remaining", &line[i], "R yo");
	r |= assert_str_eq("extract variable $VAR + VAR=Hello", ret, "Hello");
	free(ret);
	i = 0;
	ft_strlcpy(line, "${VAR}yo", 99);
	ret = extract_variable(line, &i, envp);
	r |= assert_eq("extract variable ${VAR} index", i, 6);
	r |= assert_str_eq("extract variable remaining", &line[i], "yo");
	r |= assert_str_eq("extract variable ${VAR} + VAR=Hello", ret, "Hello");
	free(ret);
	free(envp);
	r |= test_extract_variable_does_not_exist();
	return (r);
}

#endif
