/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:15:14 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 18:22:09 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static t_exp	*parse_single_exp(char *line, size_t *i, t_env e, bool is_pipe)
{
	t_exp	*exp;
	size_t	len;

	exp = (t_exp *)malloc(sizeof(t_exp));
	if (!exp)
		return (NULL);
	exp->infd = STDIN_FILENO;
	exp->outfd = STDOUT_FILENO;
	if (is_pipe)
		exp->infd = INTERNAL_PIPE_FD;
	len = exp_len(&line[*i]);
	if (!extract_args(exp, &line[*i], len, &e))
		return (free(exp), NULL);
	*i += len;
	return (exp);
}

t_exp_list	*parse(char *line, t_status *status, char **envp)
{
	t_exp_list	*head;
	void		*current;
	bool		is_pipe;
	size_t		i;

	head = NULL;
	is_pipe = false;
	i = 0;
	while (line[i])
	{
		current = parse_single_exp(line, &i, (t_env){status, envp}, is_pipe);
		if (!current)
			return (ft_lstclear((t_list **)&head, exp_free), NULL);
		current = ft_lstnew(current);
		if (!current)
			return (ft_lstclear((t_list **)&head, exp_free), NULL);
		ft_lstadd_back((t_list **)&head, current);
		is_pipe = line[i] == '|';
		if (is_pipe && ((t_exp_list *)current)->content->outfd == STDOUT_FILENO)
			((t_exp_list *)current)->content->outfd = INTERNAL_PIPE_FD;
		if (line[i])
			i++;
	}
	return (head);
}
