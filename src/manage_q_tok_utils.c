/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_q_tok_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:31:31 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/23 15:31:34 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_next_q(t_values *v, int *x, int *i, char type)
{
	(*i)++;	
	while (v->split_str[(*x)])
	{
		while(v->split_str[(*x)][(*i)])
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

void	do_copy(char *cmd_str, char *s, int *y, char type)
{
	int	i;

	i = 0;
	while (cmd_str[i] != type)
	{
		s[(*y)] = cmd_str[i];
		(*y)++;
		i++;
	}
	return ;
}

void	copy_in_cmd_str(t_values *v, char *s, int *y, int count, char type)
{
	int	i;

	i = 0;
	count *= 2;
	while(v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == type && count == 0)
		{
			do_copy(&v->cmd_str_b[i + 1], s, y, type);
			return ;
		}
		if (v->cmd_str_b[i] == type)
		{
			count--;
			i++;
		}
		i++;
	}
	return ;
}

void copy_in_tok(t_values *v, char *s, int x, char type, int count)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (v->split_str[x][i] != type)
	{
		s[y] = v->split_str[x][i];
		i++;
		y++;
	}
	copy_in_cmd_str(v, s, &y, count, type);
	go_to_next_q(v, &x, &i, type);
	while(v->split_str[x][i])
	{
		s[y] = v->split_str[x][i];
		i++;
		y++;
	}
	s[y] = 0;
	return ;
}
	





// will probably need in this function outside and inside size in order to copy the right things ?


// yes i will need to do the same thing 



// comme j'ai deja la size pour chaque truc, si je chope le x du premier token et celui de la deuxieme quote j'ai pas besoin de faire de gros calculs
