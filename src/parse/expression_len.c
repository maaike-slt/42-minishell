/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:56:57 by adelille          #+#    #+#             */
/*   Updated: 2024/12/03 22:08:46 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

size_t	expression_len(const char *line)
{
	size_t		i;
	t_escape	e;

	e.backslash = false;
	e.single_quote = false;
	e.double_quote = false;
	i = 0;
	while (line[i]
		&& ((e.backslash || e.single_quote || e.double_quote)
			|| !is_expression_separator(line[i])))
	{
		if (e.backslash)
			e.backslash = false;
		else if (line[i] == '\\')
			e.backslash = true;
		else if (line[i] == '\'' && !e.double_quote)
			e.single_quote = !e.single_quote;
		else if (line[i] == '"' && !e.single_quote)
			e.double_quote = !e.double_quote;
		i++;
	}
	return (i);
}

#ifdef TEST

bool	test_expression_len(void)
{
	bool	r;

	r = EX_OK;
	r |= assert_eq("expression_len echo \"Hello World\"",
			expression_len("echo \"Hello World\""), 18);
	r |= assert_eq("expression_len echo 'Hello World'",
			expression_len("echo 'Hello World'"), 18);
	r |= assert_eq("expression_len echo Hello World",
			expression_len("echo Hello World"), 16);
	r |= assert_eq("expression_len echo Hello World; echo here",
			expression_len("echo Hello World; echo here"), 16);
	r |= assert_eq("expression_len echo Hello\\ World",
			expression_len("echo Hello\\ World"), 17);
	r |= assert_eq("expression_len echo Hello World\\; echo here",
			expression_len("echo Hello World\\; echo here"), 28);
	r |= assert_eq("expression_len echo 'Hello World; echo here'",
			expression_len("echo 'Hello World; echo here'"), 29);
	r |= assert_eq("expression_len echo Hello World | cat -e",
			expression_len("echo Hello World | cat -e"), 17);
	r |= assert_eq("expression_len echo 'Hello World | cat -e'",
			expression_len("echo 'Hello World | cat -e'"), 27);
	r |= assert_eq("expression_len echo Hello World > file",
			expression_len("echo Hello World > file"), 23);
	return (r);
}

#endif
