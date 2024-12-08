/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:56:57 by adelille          #+#    #+#             */
/*   Updated: 2024/12/08 17:50:51 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

size_t	expression_len(const char *line)
{
	size_t		i;
	bool		backslash;
	bool		single_quote;
	bool		double_quote;

	backslash = false;
	single_quote = false;
	double_quote = false;
	i = 0;
	while (line[i]
		&& ((backslash || single_quote || double_quote)
			|| !is_expression_separator(line[i])))
	{
		if (backslash)
			backslash = false;
		else if (line[i] == '\\')
			backslash = true;
		else if (line[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (line[i] == '"' && !single_quote)
			double_quote = !double_quote;
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
