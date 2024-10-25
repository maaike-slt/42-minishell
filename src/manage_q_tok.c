/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_q_tok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:52:04 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/21 17:52:09 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_right_pos(t_values *v, int *count, char type)
{
	int	i;
	int	sec_q;
	int	temp;

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

int	get_outside_q_size(t_values *v, int x, char type)		// to explain this func, i use the split tokens to get the char that could be attached to the string, can use cmd-str_b because if there is an expand I need to use it and not the expand name, so it is easier to use split tokens
{
	int	i;
	int y;
	int	betw_q;
	int	end;

	end = 0;
	i = 0;
	betw_q = 0;
	while (v->split_str[x])
	{
		y = 0;
		while(v->split_str[x][y])
		{
			if (v->split_str[x][y] == type)			// put all of this if in an helper func for norm
			{
				if (betw_q == 0)
					betw_q = 1;
				else
				{
					betw_q = 0;
					end = 1;
					y++;
					continue ;
				}
				y++;
				continue;
			}
			if (betw_q == 0)
				i++;
			y++;
		}
		if (end)
			break;
		x++;
	}
	return (i);
}

int	get_inside_q_size(t_values *v, char type, int *count)
{
	int	i;
	int	size;

	size = 0;
	i = get_right_pos(v, count, type);		// when ls '' "" i is wrong for some reason  // ok i got it, it is because count has to be incremented by the type of quote, i need to do some struct with count for single and doube quote
	i++;
	while (v->cmd_str_b[i] != type)
	{
		size++;
		i++;
	}
	return (size);
}

int	get_size(t_values *v, int x, char type, int *count)
{
	int	out_size;
	int	in_size;

	out_size = get_outside_q_size(v, x, type);
	in_size = get_inside_q_size(v, type, count);
	return (out_size + in_size + 1);						// should i protect for ovrflow in this function ?
}

bool	manage_q_tok(t_values *v, int x, char type, int *count)		// this func, we arrived at the right split token with the first quote, and now we do the string magic to have a valdi token with quotes
{
	char *new_tok;
	int	size;

	size = get_size(v, x, type, count);		//for malloc
	new_tok = malloc(sizeof(char) * size);
	if (!new_tok)
		return (false);
	copy_in_tok(v, new_tok, x, type, count);
	manage_rest_tok(v, x, new_tok, type);
	return (true);
}



// make a token for the quote
// integrate the token in the split
// manipulate and free the rest of the tokens

// there will be be probably a problem when trying to free the split str at exit of readline loop pass, probably will need to do some kind of if (split[i]) -> free





















	












// pour le truc d'avoir aussi les charactères qui viennent avant la quote potentiellement, et après. Ouai en fait je peux faire avec les token de split
// en fait ce sera beaucoup plus simple je pense, genre je compte jusqu'au whitespace après la deuxième quote et je pense qu'on est bon, meme avec les
// expand et tout, simplement grace au fait qu'on doit laisser les trous dans les expands, donc avec la quote je vais jusqu'au trou et c'est bon
// -> tester
// oui, a premiere vue ça fonctionne comme ça, donc c'est encore plus simple que ce que j'imaginais comme parsing


// d'abord choper la len du malloc, ensuite copier tout ça, puis manager les char *





// ah ouai mais je vais avoir un probleme, j'ai pas les whitespaces dans les splits, et donc si je fais pas avec la cmd_str_b j'aurais pas les bons
// whitespace si quelqu'un a mis un tab, mais d'un autre coté si je fais totalement avec la cmd_str_b j'aurais pas les expand.
// probablement ce que je peux faire c'est que je fais avec le split tant que je suis pas dans les quotes, et je fais avec la cmd_str_b dès que je suis
//dans les quotes, et dès que je sors des quotes je reregarder dans les split et je continue si il y a quelque chose après, expand ou autre, parce que 
// de toute manière ce que je dois préservé ce sont les whitespaces a l'intérieur des quotes, normalement une fois qu'on est en dehors si j'ai bien 
// compris 
