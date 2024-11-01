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

int	next_pos(t_values *v, t_quote *q, int x, int y)
{
	y++;
	while(v->split_str[x][y])
	{
		if (if_pass_check(v->split_str[x][y], &q->tab[q->z], q) == false)
		{
			q->pos = y;
			q->count_next_quote++;
			return (0);
		}
		y++;
	}
	q->pos = -1;
	return (-1);
}

size_t	get_right_pos(t_values *v, int *count, char type)
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
	int	y;
	bool	betw_q;
	bool	end;
	bool	sec_valid_q;
	int		temp;
	char	temp_type;
	int		temp_z;

	temp = q->pos;
	temp_type = q->type;
	temp_z = q->z;
	end = false;
	betw_q = false;
	sec_valid_q = false;
	i = 0;						// pls don't change this, i needs to be outside the loop
	while (v->split_str[x])
	{
		y = 0;
		while (v->split_str[x][y])
		{
			if (y == q->pos)
			{
				sec_valid_q = true;
				if (betw_q == false)
					betw_q = true;
				else
				{
					betw_q = false;			//this loop is broken, 
					end = true;
					y++;
					continue ;
				}
				y++;
				continue ;
			}
			if (v->split_str[x][y] == q->type && sec_valid_q == true)
			{
				sec_valid_q = false;
				if (next_pos(v, q, x, y) == -1)
					end = true;
				betw_q = false;
				y++;
				continue ;
			}
			if (betw_q == false)
				i++;
			y++;
		}
		if (q->pos == 0)
			q->pos = -1;
		if (end)
			break ;
		x++;
	}
	q->pos = temp;
	q->type = temp_type;
	q->z = temp_z;
	return (i);
}

static size_t	get_inside_q_size(t_values *v, char type, int *count, t_quote *q)
{
	size_t	i;
	size_t	size;

	size = 0;
	i = get_right_pos(v, count, type);
	i++;
	while (v->cmd_str_b[i] != type || q->count_next_quote)
	{
		if (v->cmd_str_b[i] == type && q->count_next_quote)	
		{
			i++;
			while (v->cmd_str_b[i] && v->cmd_str_b[i] != '\'' && v->cmd_str_b[i] != '\"')
				i++;
			type = v->cmd_str_b[i];
			if (v->cmd_str_b[i])
				i++;
			q->count_next_quote--;			// pour que la version copy fonctionne j'aurais prob besoin de temp ça count next_quote
			continue ;
		}
		size++;
		i++;
	}
	return (size);
}

static size_t	get_size(t_values *v, t_quote *q)
{
	size_t	out_size;
	size_t	in_size;
	size_t new_tok_size;

	out_size = get_outside_q_size(v, q->x, q);		// pls don't touch x access, pass by value needed
	in_size = get_inside_q_size(v, q->type, q->count, q);
	new_tok_size = out_size + in_size + 1;
	q->new_tok_size = new_tok_size;
	return (new_tok_size);
}

bool	manage_q_tok(t_values *v, t_quote *q)
{
	char	*new_tok;
	size_t	size;

	size = get_size(v, q);
	new_tok = malloc(sizeof(char) * size);
	if (!new_tok)
		return (false);
	ft_bzero(new_tok, size);
	copy_in_tok(v, new_tok, q->x, q);			// pls don't change x, pass by value needed
	manage_rest_tok(v, new_tok, q);
	return (true);
}
