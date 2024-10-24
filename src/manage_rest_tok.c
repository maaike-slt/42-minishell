/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rest_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:35 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/23 17:15:36 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_type(char *s, char type)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == type)
			return (1);
		i++;
	}
	return (0);
}

int	free_useless_tok(t_values *v, int x, char type)
{
	int	i;
	int result;

	i = 0;
	x++;
	result = is_there_type(v->split_str[x], type);
	while (result != -1 && result != 1)
	{
		free(v->split_str[x]);
		x++;
		result = is_there_type(v->split_str[x], type);
	}
	free(v->split_str[x]);
	return (x);
}

int		move_tokens(t_values *v, int x, int sec_q_tok)
{
	int	i;

	i = 0;
	sec_q_tok++;
	x++;
	if (!(v->split_str[x]))
		return (x);
	while (v->split_str[sec_q_tok])
	{
		v->split_str[x] = v->split_str[sec_q_tok];
		sec_q_tok ++;
		x++;
	}
	return (x);
}

void	manage_rest_tok(t_values *v, int x, char *new_tok, char type)
{
	int	sec_q_tok;
	int	last_viable_tok;
	int	temp;

	free(v->split_str[x]);
	v->split_str[x] = new_tok;
	sec_q_tok = free_useless_tok(v, x, type);
	last_viable_tok = move_tokens(v, x, sec_q_tok);
	temp = last_viable_tok;
	v->split_str[temp] = NULL;
	while (v->split_str[last_viable_tok])
	{
		free(v->split_str[last_viable_tok]);
		last_viable_tok++;
	}
	return ;
}
	
