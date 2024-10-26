/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:25:05 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:47:47 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static bool	if_pass_check(char c, int *tab, int *z)
static bool	if_pass_check(char c, int *tab, t_quote *q)
{
	if (c == '\'' || c == '\"')
	{
		if (*tab == 0)
		{
			(q->z)++;
			q->pos = q->y;
			return (false);
		}
		else
		{
			(*tab)--;
			return (true);
		}
	}
	return (true);
}

static void	init_quote(t_quote *q, int *tab)
{
	q->x = 0;
	q->y = 0;
	q->z = 0;
	q->type = 0;
	q->tab = tab;
	q->pos = 0;
	q->count['\''] = 0;
	q->count['\"'] = 0;
}

bool	quote_parsing(t_values *v, int	*tab)
{
	t_quote q;

	init_quote(&q, tab);
	while (v->split_str[q.x])
	{
		q.y = 0;
		while (v->split_str[q.x][q.y])
		{
//			if (if_pass_check(v->split_str[q.x][q.y], &tab[q.z], &q.z)	== false)
			if (if_pass_check(v->split_str[q.x][q.y], &tab[q.z], &q)	== false)
			{
				int lol= 0;
				while (v->split_str[lol])
				{
					printf("%s\n", v->split_str[lol]);
					lol++;
				}
				printf("STOP\n");
				q.type = v->split_str[q.x][q.y];
				if (manage_q_tok(v, &q) == false)
					return (false);
				(q.count[(int)q.type])++;
				break ;
			}
			q.y++;
		}
		q.x++;
	}
	return (true);
}
