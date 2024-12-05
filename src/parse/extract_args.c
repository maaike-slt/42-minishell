/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:14:59 by adelille          #+#    #+#             */
/*   Updated: 2024/12/05 21:13:04 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static char	*extract_single_arg(
	const char *line, size_t *i, size_t len, char **envp)
{
	size_t	start;
	size_t	checkpoint;
	char	quote;
	char	*ret;

	ret = NULL;
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	quote = '\0';
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
	}
	start = *i;
	checkpoint = *i;
	while (!is_arg_separator(line[*i], quote) && *i - start < len)
	{
		if (line[*i] == '\\')
			*i += 2;
		else if (line[*i] == '$')
		{
			// FIXME: handle variables
			(*i)++;
		}
		else
			(*i)++;
	}
	return (ft_strjoin_free(ret,
			ft_strndup(&line[checkpoint], *i - checkpoint), true, true));
}

bool	extract_args(t_expression *exp, char *line, size_t len, char **envp)
{
	size_t	i;
	t_arr	arr;
	bool	escape;
	bool	single_quote;
	bool	double_quote;

	(void)envp;
	exp->argc = 0;
	if (!ft_arr_new(&arr, sizeof(char *)))
		return (false);
	i = 0;
	while (i < len)
	{
		if (escape)
		{
			ft_arr_add(&arr, &line[i]);
			escape = false;
			i++;
			continue ;
		}
		if (line[i] == '\\')
			escape = true;
		else if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (ft_isspace(line[i]) && !single_quote && !double_quote)
		{
			//
		}
		else
		{
			// FIXME: handle variables
			ft_arr_add(&arr, &line[i]);
		}
		i++;
	}
	return (true);
}
