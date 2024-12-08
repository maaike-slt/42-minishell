/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:15:14 by adelille          #+#    #+#             */
/*   Updated: 2024/12/08 18:47:51 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static t_expression	*parse_single_expression(char *line, size_t *i, char **envp)
{
	t_expression	*exp;
	size_t			len;

	exp = (t_expression *)malloc(sizeof(t_expression));
	if (!exp)
		return (NULL);
	len = expression_len(&line[*i]);
	if (!extract_args(exp, &line[*i], len, envp))
		return (free(exp), NULL);
	*i += len;
	return (exp);
}

t_expression_list	*parse(char *line, char **envp)
{
	t_expression_list	*head;
	void				*current;
	size_t				i;

	if (!line || line[0] == '\0')
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		current = parse_single_expression(line, &i, envp);
		if (!current)
			return (ft_lstclear((t_list **)&head, expression_free), NULL);
		current = ft_lstnew(current);
		if (!current)
			return (ft_lstclear((t_list **)&head, expression_free), NULL);
		ft_lstadd_back((t_list **)&head, current);
		/* i++; */
	}
	return (head);
}
