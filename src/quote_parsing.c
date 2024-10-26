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

static bool	pass_check(char c, int *tab, int *z)
{
	if (c == '\'' || c == '\"')
	{
		if (*tab == 0)
		{
			(*z)++;
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
	q->count['\''] = 0;
	q->count['\"'] = 0;
}

bool	quote_parsing(t_values *v, int	*tab)		// here i need to do a struct with count to have count->single or something like this
{
	t_quote q;

	init_quote(&q, tab);
	while (v->split_str[q.x])
	{
		q.y = 0;
		while (v->split_str[q.x][q.y])
		{
			if (pass_check(v->split_str[q.x][q.y], &tab[q.z], &q.z)	== false)
			{
				q.type = v->split_str[q.x][q.y];
				if (manage_q_tok(v, &q) == false)
					return (false);
				(q.count[(int)q.type])++;							// je peux peut etre faire une fonction ici pour incrémenter le bon type, ça prendrais qu'une seule ligne
				break ;
			}
			q.y++;
		}
		q.x++;
	}
	return (true);
}
