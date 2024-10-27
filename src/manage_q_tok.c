/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_q_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:52:04 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 16:37:24 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_right_pos(t_values *v, int *count, char type)
{
	size_t	i;
	size_t	sec_q;
	int	temp;

	i = 0;
	sec_q = 0;
	temp = count[(int)type];
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == type && count[(int)type] == 0)
		{
			count[(int)type] = temp;
			return (i);
		}
		if (v->cmd_str_b[i] == type)
		{
			if (sec_q == 0)
				sec_q = 1;
			else
			{
				sec_q = 0;
				(count[(int)type])--;
			}
		}
		i++;
	}
	count[(int)type] = temp;
	return (i);
}

static size_t	get_outside_q_size(t_values *v, int x, t_quote *q)
{
	size_t	i;
	size_t	y;
	bool	betw_q;
	bool	end;

	end = false;
	betw_q = false;
	i = 0;						// DON'T CHANGE THIS, you introduced a bug here, i has to be incremented even if x changes, if you put i in the loop when x changes size will not be accurate
	while (v->split_str[x])
	{
		y = 0;
		while (v->split_str[x][y])
		{
			if (y == q->pos)
			{
				if (betw_q == false)
					betw_q = true;
				else
				{
					betw_q = false;
					end = true;
					y++;
					continue ;
				}
				y++;
				continue ;
			}
			if (v->split_str[x][y] == q->type)			//this probably won't work with ls aaa'test'$envvarwithquotes'test'aaa
				betw_q = false;
			if (betw_q == false)
				i++;
			y++;
		}
		if (end)
			break ;
		x++;
	}
	return (i);
}

static size_t	get_inside_q_size(t_values *v, char type, int *count)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = get_right_pos(v, count, type);
	i++;
	while (v->cmd_str_b[i] != type)
	{
		size++;
		i++;
	}
	return (size);
}

static size_t	get_size(t_values *v, t_quote *q)
{
	size_t	out_size;
	size_t	in_size;

	out_size = get_outside_q_size(v, q->x, q);		// don't touch q access , sometimes pass by value needed, sometimes pointer
	in_size = get_inside_q_size(v, q->type, q->count);
	return (out_size + in_size + 1);
}

bool	manage_q_tok(t_values *v, t_quote *q)
{
	char	*new_tok;
	size_t	size;

	size = get_size(v, q);
	new_tok = malloc(sizeof(char) * size);
	if (!new_tok)
		return (false);
	copy_in_tok(v, new_tok, q->x, q);			// x pass by value needed, don't change
	manage_rest_tok(v, new_tok, q);
	return (true);
}
