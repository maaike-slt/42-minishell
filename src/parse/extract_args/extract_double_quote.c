/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_double_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:11 by adelille          #+#    #+#             */
/*   Updated: 2025/02/23 17:59:53 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

char	*extract_double_quote(const char *line, size_t *i)
{
	char	*ret;

	(*i)++;
	ret = ft_strdup("");
	while (ret && line[*i] && line[*i] != '"')
	{
		if (line[*i] == '\\' && ft_is_in("\\\"$", line[*i + 1]))
		{
			(*i)++;
			ft_strpush(&ret, line[*i]);
		}
		else if (line[*i] == '$')
			ret = ft_strjoin_free(ret, mark_var(line, i), true, true);
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

	ft_strlcpy(line, "\"He;llo\\ Wor\\$ld \\\"  here  \"   ", 99);
	i = 0;
	ret = extract_double_quote(line, &i);
	r = EX_OK;
	r |= assert_eq("extract_double_quote index", i, 27);
	r |= assert_str_eq("extract_double_quote remaining", &line[i], "\"   ");
	r |= assert_str_eq("extract_double_quote return",
			ret, "He;llo\\ Wor$ld \"  here  ");
	free(ret);
	return (r);
}

#endif
