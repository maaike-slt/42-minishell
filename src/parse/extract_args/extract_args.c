/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:14:59 by adelille          #+#    #+#             */
/*   Updated: 2024/12/08 16:48:37 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static char *extract_double_quote(const char *line, size_t *i)
{
}

static char *extract_single_quote(const char *line, size_t *i)
{
}

static char	*extract_single_arg(
	const char *line, size_t *i, size_t len, char **envp)
{
	char	*ret;

	ret = ft_strdup("");
	while (ret && *i < len && line[*i] && !ft_isspace(line[*i]))
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
			ret = ft_strjoin_free(ret, extract_variable(line, i, envp), true, true);
		else
			ft_strpush(&ret, line[*i]);
		(*i)++;
	}
	return (ret);
}

bool	extract_args(t_expression *exp, char *line, size_t len, char **envp)
{
	t_arr	arr;
	char	*arg;
	size_t	i;

	if (!ft_arr_new(&arr, sizeof(char *)))
		return (false);
	i = 0;
	while (i < len)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		arg = extract_single_arg(line, &i, len, envp);
		if (!arg || !ft_arr_add(&arr, arg))
			return (ft_free_2d((void **)arr.p), false);
	}
	exp->argc = arr.len;
	exp->argv = (char **)arr.p;
	return (true);
}

#ifdef TEST

bool	test_extract_args(void)
{
	t_expression	exp;
	char			**envp = NULL;

	if (!extract_args(&exp, "yo \"ye; no\" 'oh | e'\", ft_strlen(line), envp))
		return (false);
	if (exp.argc != 2)
		return (false);
	if (ft_strcmp(exp.argv[0], "echo") != 0)
		return (false);
	if (ft_strcmp(exp.argv[1], "Hello, World!") != 0)
		return (false);
	return (true);
}

#endif
