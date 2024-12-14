/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:15:14 by adelille          #+#    #+#             */
/*   Updated: 2024/12/14 17:31:45 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static t_exp	*parse_single_exp(char *line, size_t *i, char **envp)
{
	t_exp	*exp;
	size_t	len;

	exp = (t_exp *)malloc(sizeof(t_exp));
	if (!exp)
		return (NULL);
	len = exp_len(&line[*i]);
	if (!extract_args(exp, &line[*i], len, envp))
		return (free(exp), NULL);
	*i += len;
	return (exp);
}

t_exp_list	*parse(char *line, char **envp)
{
	t_exp_list	*head;
	void		*current;
	size_t		i;

	if (!line || line[0] == '\0')
		return (NULL);
	head = NULL;
	i = 0;
	while (line[i])
	{
		current = parse_single_exp(line, &i, envp);
		if (!current)
			return (ft_lstclear((t_list **)&head, exp_free), NULL);
		current = ft_lstnew(current);
		if (!current)
			return (ft_lstclear((t_list **)&head, exp_free), NULL);
		ft_lstadd_back((t_list **)&head, current);
		if (line[i])
			i++;
	}
	return (head);
}
