/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_q_tok_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:31:31 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:37:17 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	go_to_next_q(t_values *v, int *x, size_t *i, char type)
{
	(*i)++;
	while (v->split_str[(*x)])
	{
		while (v->split_str[(*x)][(*i)])
		{
			if (v->split_str[(*x)][(*i)] == type)
			{
				(*i)++;
				return ;
			}
			(*i)++;
		}
		(*i) = 0;
		(*x)++;
	}
	return ;
}

static void	do_copy(char *cmd_str, char *s, size_t *y, char type)
{
	size_t	i;

	i = 0;
	while (cmd_str[i] != type)
	{
		s[(*y)] = cmd_str[i];
		(*y)++;
		i++;
	}
	return ;
}

static void	copy_in_cmd_str(t_values *v, char *s, size_t *y, t_quote *q)
{
	int	temp;
	size_t	i;

	i = 0;
	temp = q->count[(int)q->type];
	q->count[(int)q->type] *= 2;
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == q->type && q->count[(int)q->type] == 0)
		{
			q->count[(int)q->type] = temp;
			do_copy(&v->cmd_str_b[i + 1], s, y, q->type);
			return ;
		}
		if (v->cmd_str_b[i] == q->type)
		{
			(q->count[(int)q->type])--;
			i++;
		}
		i++;
	}
	q->count[(int)q->type] = temp;
	return ;
}

void copy_in_tok(t_values *v, char *s, int x, t_quote *q)	
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
//	while (v->split_str[x][i] != q->type)
	while (i != q->pos)
	{
		s[y] = v->split_str[x][i];
		i++;
		y++;
	}
	copy_in_cmd_str(v, s, &y, q);
	go_to_next_q(v, &x, &i, q->type);  //continue here
	while (v->split_str[x][i])
	{
		if (v->split_str[x][i] == '\'' || v->split_str[x][i] == '\"')		// for case ls '''''''' or ls ''""''""''""
			break ;
		s[y] = v->split_str[x][i];
		i++;
		y++;
	}
	s[y] = 0;
	return ;
}
