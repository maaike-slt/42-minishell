/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:14:59 by adelille          #+#    #+#             */
/*   Updated: 2024/12/01 22:26:16 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

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
