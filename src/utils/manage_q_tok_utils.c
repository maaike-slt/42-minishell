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

//static void	go_to_next_q(t_values *v, int *x, size_t *i, char type)
//{
//	(*i)++;
//	while (v->split_str[(*x)])
//	{
//		while (v->split_str[(*x)][(*i)])
//		{
//			if (v->split_str[(*x)][(*i)] == type)
//			{
//				(*i)++;
//				return ;
//			}
//			(*i)++;
//		}
//		(*i) = 0;
//		(*x)++;
//	}
//	return ;
//}
//
//static void	do_copy(char *cmd_str, char *s, size_t *y, char type)
//{
//	size_t	i;
//
//	i = 0;
//	while (cmd_str[i] != type)
//	{
//		s[(*y)] = cmd_str[i];
//		(*y)++;
//		i++;
//	}
//	return ;
//}
//
////static void manage_type_counter
//
//static void	copy_in_cmd_str(t_values *v, char *s, size_t *y, t_quote *q)
//{
//	int	temp;
//	size_t	i;
//
//	i = 0;
//	temp = q->count[(int)q->type];
////	manage_type_counter(q);
//	q->count[(int)q->type] *= 2;
//	while (v->cmd_str_b[i])
//	{
//		if (v->cmd_str_b[i] == q->type && q->count[(int)q->type] == 0)
//		{
//			do_copy(&v->cmd_str_b[i + 1], s, y, q->type);
//			q->count[(int)q->type] = temp;
//			return ;
////			if (q->count_next_quote == 0)						// for potential next quote in same split token i will to check for other type also
////			{
////				q->count[(int)q->type] = temp;				// ah je peux faire une fonction search next type si je dois continuer la search
////				return ;
////			}
////			q->count_next_quote--;							// problem, if type is different on encounter new quote in cmdr_str_b, need to manage count[type] somehow for next iteration
//		}
//		if (v->cmd_str_b[i] == q->type)
//		{
//			(q->count[(int)q->type])--;
//			i++;
//			continue ;
//		}
//		i++;
//	}
//	q->count[(int)q->type] = temp;
//	return ;
//}

//void copy_in_tok(t_values *v, char *s, int x, t_quote *q)	
//{
//	size_t	i;
//	size_t	y;
//
//	i = 0;
//	y = 0;
//	while (i != q->pos)
//	{
//		s[y] = v->split_str[x][i];
//		i++;
//		y++;
//	}
//	copy_in_cmd_str(v, s, &y, q);			//count should only be manipulated in / after this func
//	go_to_next_q(v, &x, &i, q->type);
//	while (v->split_str[x][i])
//	{
//		if (v->split_str[x][i] == '\'' || v->split_str[x][i] == '\"')		// for case ls '''''''' or ls ''""''""''""
//			break ;
//		s[y] = v->split_str[x][i];
//		i++;
//		y++;
//	}
//	s[y] = 0;
//	return ;
//}






static size_t	get_next_i(t_values *v, size_t count_next_quote)
{
	size_t	i;
	size_t	size;
	char	type;
	static size_t	calc_right_size; 		// otherwise on second pass size will be grom the beginning and not wht is needed 
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
					size -= calc_right_size;
					calc_right_size = temp;
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
	size_t	y;
	bool	betw_q;
	bool	end;
	bool	sec_valid_q;
	int		temp;
	char	temp_type;

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
				i += get_next_i(v, q->count_next_quote);
				if (next_pos(v, q, x, y) == -1)
					end = true;
				betw_q = false;
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
		if (q->pos == 0)
			q->pos = -1;
		if (end)
			break ;
		x++;
	}
	q->pos = temp;
	q->type = temp_type;
	return ;
}

static void	copy_inside(t_values *v, int *count, t_quote *q, char *new_tok)		//copy inside		// probleme ici je dois pouvoir mettre new tok en arg, mais ca fera 5, dois checker si pass by pointer here is faisable
{
	size_t	i;
	size_t y;
	char type;

	y = 0;
	type = q->type;
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
			type = v->cmd_str_b[i];				// aussi pour que copy fonctionne, je dois temp le type ici// NON PARCE QUE PASS BY VALUE, mais justement je vais changer ça
			i++;
			q->count_next_quote--;			// pour que la version copy fonctionne j'aurais prob besoin de temp ça count next_quote		//non je pense pas parce que normalement la fonction copy outside recalcule le truc
			skip_char(new_tok, &y);
			continue ;
		}
		new_tok[y] = v->cmd_str_b[i];
		y++;
		i++;
	}
	return ;
}

void copy_in_tok(t_values *v, char *s, int x, t_quote *q)	
{
	copy_outside(v, x, q, s);
	copy_inside(v, q->count, q, s); 
	s[(q->new_tok_size - 1)] = 0;
	return ;
}
