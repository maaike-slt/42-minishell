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
//<<<<<<< HEAD
//	int	i;
//	int	sec_q;
//	int	temp;
//=======
	size_t	i;
	size_t	sec_q;
	int	temp;
//>>>>>>> refs/remotes/origin/main

	i = 0;
	sec_q = 0;
	temp = count[(int)type];
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == type && count[(int)type] == 0)		//   0 not right here
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
				sec_q = 0;					// will this be accurate with different quotes ? I think so, it doesnt matter for count which type of quotes it is, as long as quotes are valid, i think
				(count[(int)type])--;
			}
		}
		i++;
	}
	count[(int)type] = temp;
	return (i);
}

static size_t	get_outside_q_size(t_values *v, int x, char type)		// to explain this func, i use the split tokens to get the char that could be attached to the string, can use cmd-str_b because if there is an expand I need to use it and not the expand name, so it is easier to use split tokens
{
	size_t	i;
	size_t	y;
	bool	betw_q;
	bool	end;

	end = false;
	betw_q = false;
	while (v->split_str[x])
	{
		i = 0;
		y = 0;
		while (v->split_str[x][y])
		{
			if (v->split_str[x][y] == type)			// put all of this if in an helper func for norm
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

static size_t	get_size(t_values *v, int x, char type, int *count)
{
	size_t	out_size;
	size_t	in_size;

	out_size = get_outside_q_size(v, x, type);
	in_size = get_inside_q_size(v, type, count);
	return (out_size + in_size + 1);						// should i protect for ovrflow in this function ?
}

bool	manage_q_tok(t_values *v, int x, char type, int *count)		// this func, we arrived at the right split token with the first quote, and now we do the string magic to have a valdi token with quotes
{
	char	*new_tok;
	size_t	size;

	size = get_size(v, x, type, count);		//for malloc
	new_tok = malloc(sizeof(char) * size);
	if (!new_tok)
		return (false);
	copy_in_tok(v, new_tok, x, type, count);
	manage_rest_tok(v, x, new_tok, type);
	return (true);
}
