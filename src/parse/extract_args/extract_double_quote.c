/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_double_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:11 by adelille          #+#    #+#             */
/*   Updated: 2024/12/08 17:04:48 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_double_quote(const char *line, size_t *i, char **envp)
{
	char	*ret;

	(void)envp;
	(*i)++;
	ret = ft_strdup("");
	while (ret && line[*i] && line[*i] != '"')
	{
		if (line[*i] == '\\')
		{
			(*i)++;
			ft_strpush(&ret, line[*i]); 
		}
		/*
		else if (line[*i] == '$')
			ret = ft_strjoin_free(ret, extract_variable(line, i, envp), true, true);
		*/
		else
			ft_strpush(&ret, line[*i]); 
		(*i)++;
	}
	return (ret);
}

#ifdef TEST

bool	test_extract_double_quote(void)
{
	char	line[99];
	size_t	i;
	char	*ret;
	bool	r;

	ft_strlcpy(line, "\"He;llo\\ Wor$ld \\\"  here  \"   ", 99);
	i = 0;
	ret = extract_double_quote(line, &i);
	r = EX_OK;
	r |= assert_eq("extract_double_quote index", i, 19);
	r |= assert_str_eq("extract_double_quote ending char", &line[i], "\'");
	r |= assert_str_eq("extract_double_quote return",
			ret, "He;llo\\ Wor$ld \\'");
	free(ret);
	return (r);
}

#endif
