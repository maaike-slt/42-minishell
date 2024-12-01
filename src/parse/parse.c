/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:15:14 by adelille          #+#    #+#             */
/*   Updated: 2024/12/01 22:16:49 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static t_expression	*parse_single_expression(char *line, size_t *i)
{
	t_expression	*exp;
	t_arr			arr;

	exp = (t_expression *)malloc(sizeof(t_expression));
	if (!exp)
		return (NULL);
	exp->argc = 0;
	if (!ft_arr_new(&arr, sizeof(char *)))
	{
		free(exp);
		return (NULL);
	}
	while (line[*i] && !is_separator(line[*i]))
	{
		if (!ft_arr_add(&arr, &line[*i]))
		{
			free(arr.p);
			free(exp);
			return (NULL);
		}
		(*i)++;
	}
	return (exp);
}

t_expression_list	*parse(char *line)
{
	t_expression_list	*head;
	size_t				i;

	if (!line || line[0] == '\0')
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		parse_single_expression(line, &i);
		i++;
	}
	return (head);
}
