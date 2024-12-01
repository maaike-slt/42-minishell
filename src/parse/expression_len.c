/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:56:57 by adelille          #+#    #+#             */
/*   Updated: 2024/12/01 22:29:21 by adelille         ###   ########.fr       */
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
		&& (e.backslash || e.single_quote || e.double_quote)
		&& !is_separator(line[i]))
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
int	main(void)
{
	char	*line = "echo \"Hello World\"";
	size_t	len;

	len = expression_len(line);
	printf("len: %zu\n", len);
	return (0);
}
#endif
