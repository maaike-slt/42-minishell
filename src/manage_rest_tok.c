/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rest_tok.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:35 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/23 21:16:15 by msloot           ###   ########.fr       */
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

int	is_there_two_type(char *s, char type)
{
	int	i;
	int	count;

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

int	free_useless_tok(t_values *v, int x, char type)
{
	int result;

	x++;
	result = is_there_type(v->split_str[x], type);
	while (result != -1 && result != 1)						// here why not result ==0 ?			// this loop likely is not correct // no it is correct i think
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

void	manage_rest_tok(t_values *v, int x, char *new_tok, char type)
{
	int	sec_q_tok;
	int	last_viable_tok;
	int	temp;
	char *old_tok;

	old_tok = v->split_str[x];
	v->split_str[x] = new_tok;
	if (is_there_two_type(old_tok, type))
	{
		free(old_tok);
		return ;
	}
	free(old_tok);
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
