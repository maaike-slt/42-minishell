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

static size_t	get_next_i(t_values *v, size_t count_next_quote, size_t *calc_right_size)
{
	size_t	i;
	size_t	size;
	char	type;
	size_t	temp;

	i = 0;
	size = 0;
	type = 0;
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')
		{
			if (type && type == v->cmd_str_b[i])
			{
				if (!count_next_quote)
				{
					temp = size;
					size -= *calc_right_size;
					*calc_right_size = temp;
					return (size);
				}
				count_next_quote--;
				type = 0;
				i++;
				continue ;
			}
			if (!type)
			{
				type = v->cmd_str_b[i];
				i++;
				continue ;
			}
		}
		if (type)
			size++;
		i++;
	}
	return (size + 1);
}


static void	skip_char(char *new_tok, size_t *i)
{
	while(new_tok[(*i)])
		(*i)++;
	return ;
}

static void	copy_outside(t_values *v, int x, t_quote *q, char *new_tok)		// copy_outside
{
	size_t	i;
	int	y;
	bool	betw_q;
	bool	end;
	bool	sec_valid_q;
	int		temp;
	char	temp_type;
	static size_t	calc_right_size; 	//size wrong on sec pass otherwise

	temp = q->pos;
	temp_type = q->type;
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
				q->pos = -1;
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
			if (v->split_str[x][y] == q->type && sec_valid_q == true)
			{
				sec_valid_q = false;
				i += get_next_i(v, q->count_next_quote, &calc_right_size);
				betw_q = false;				//avant avant y++
				if (next_pos(v, q, x, y) == -1)
//				{
//					betw_q = false;		// ajout			/ cas 'ls' ''''''					/// PERHAPS FIXED, CHECK ALL CASES
					end = true;					// probleme ici pour cas ls aaaaa'     'aaaa
//				}
				y++;
				continue ;
			}
			if (betw_q == false)
			{
				new_tok[i] = v->split_str[x][y];
				i++;
			}
			y++;
		}
//		if (q->pos == 0)
//			q->pos = -1;
		if (end)
			break ;
		x++;
	}
	q->pos = temp;
	q->type = temp_type;
	calc_right_size = 0;
	return ;
}

static void	copy_inside(t_values *v, int *count, t_quote *q, char *new_tok)
{
	size_t	i;
	size_t y;
	char type;
	size_t temp;

	y = 0;
	type = q->type;
	temp = q->count_next_quote;
	i = get_right_pos(v, count, type);
	i++;
	skip_char(new_tok, &y);
	while (v->cmd_str_b[i] != type || q->count_next_quote)
	{
		if (v->cmd_str_b[i] == type && q->count_next_quote)	
		{
			i++;
			while (v->cmd_str_b[i] != '\'' && v->cmd_str_b[i] != '\"')
				i++;
			type = v->cmd_str_b[i];
			i++;
			q->count_next_quote--;
			skip_char(new_tok, &y);
			continue ;
		}
		new_tok[y] = v->cmd_str_b[i];
		y++;
		i++;
	}
	q->count_next_quote = temp;
	return ;
}

void copy_in_tok(t_values *v, char *s, int x, t_quote *q)	
{
	copy_outside(v, x, q, s);
	copy_inside(v, q->count, q, s); 
	s[(q->new_tok_size - 1)] = 0;
	return ;
}
