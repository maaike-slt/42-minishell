/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_single_quote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:11 by adelille          #+#    #+#             */
/*   Updated: 2024/12/14 18:07:39 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

char	*extract_single_quote(const char *line, size_t *i)
{
	size_t	start;

	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	return (ft_strndup(&line[start], *i - start));
}

#ifdef TEST

bool	test_extract_single_quote(void)
{
	char	line[99];
	size_t	i;
	char	*ret;
	bool	r;

	ft_strlcpy(line, "'He;llo\\ Wor$ld \\'    '", 99);
	i = 0;
	ret = extract_single_quote(line, &i);
	r = EX_OK;
	r |= assert_eq("extract_single_quote index", i, 17);
	r |= assert_str_eq("extract_single_quote ending char", &line[i], "'    '");
	r |= assert_str_eq("extract_single_quote return",
			ret, "He;llo\\ Wor$ld \\");
	free(ret);
	return (r);
}

#endif
