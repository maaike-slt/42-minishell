/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rest_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:35 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 16:26:58 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_type(char *s, char type)
{
	size_t	i;

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

static int	has_two_types(char *s, char type)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == type)
		{
			if (count == 1)
				return (1);
			else
				count++;
		}
		i++;
	}
	return (0);
}

static size_t	free_useless_tok(t_values *v, size_t x, char type)
{
	int	res;

	x++;
	res = has_type(v->split_str[x], type);
	while (res != -1 && res != 1)						// here why not result ==0 ?			// this loop likely is not correct // no it is correct i think
	{
		free(v->split_str[x]);
		x++;
		res = has_type(v->split_str[x], type);
	}
	free(v->split_str[x]);
	return (x);
}

static size_t	move_tokens(t_values *v, size_t x, size_t sec_q_tok)
{
	sec_q_tok++;
	x++;
	if (!(v->split_str[x]))		// no this is not right		// yes, is some case this can point to a freed token  // I think v->split_str[sec_q_tok] in the check ws a good idea // i think this protec is meaningless // have to redo all of this function
		return (x);
	while (v->split_str[sec_q_tok])
	{
		v->split_str[x] = v->split_str[sec_q_tok];
		sec_q_tok++;
		x++;
	}
	return (x);
}
void	manage_rest_tok(t_values *v, char *new_tok, t_quote *q)
{
	size_t	sec_q_tok;
	size_t	last_viable_tok;
	size_t	tmp;
	char	*old_tok;

	old_tok = v->split_str[q->x];
//	old_tok_pos = &v->split_str[q->x][q->pos];
	v->split_str[q->x] = new_tok;
	if (has_two_types(&old_tok[q->pos], q->type))
	{
		free(old_tok);
		return ;
	}
	free(old_tok);
	sec_q_tok = free_useless_tok(v, q->x, q->type);
	last_viable_tok = move_tokens(v, q->x, sec_q_tok);
	tmp = last_viable_tok;
	v->split_str[tmp] = NULL;
	while (v->split_str[last_viable_tok])
	{
		free(v->split_str[last_viable_tok]);
		last_viable_tok++;
	}
	return ;
}
