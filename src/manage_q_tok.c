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

int	get_right_pos(t_values *v, int count)
{
	int	i;
	int	sec_q;

	i = 0;
	sec_q = 0;
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == type && count == 0)
			return (i);
		if (v->cmd_str_b[i] == type)
		{
			if (sec_q = 0)
				sec_q = 1;
			else
			{
				sec_q = 0;					// will this be accurate with different quotes ? I think so, it doesnt matter for count which type of quotes it is, as long as quotes are valid, i think
				count--;
			}
		}
		i++;
	}
	return (i);
}

int	get_outside_q_size(t_values *v, int x, char type)
{
	int	i;
	int y;
	int	betw_q;
	int	end;

	count = 0;
	end = 0;
	while (v->split_str[x])
	{
		y= 0;
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
			}
			if (betw_q == 0)
				i++;
			y++;
		}
		if (end)
			break;
		x++;			// need a way to not got to the end of the split but only last split token after second quote 
	}
	return (i);   // ah ouai mais comme ça j'ai pas la size, il me faut aussi la size entre les quotes, et aussi -2 pour enlever les quotes, +1 pour null term
}

int	get_inside_q_size(t_values *v, char type, count)
{
	int	i;
	int	size;

	size = 0;
	i = get_right_pos(v, count);
	while (v->cmd_str_b[++i] != type)
	{
		size ++;
		i++;
	}
	return (i);
}
		
		
	
	

int	get_size(t_values *v, int x, char type)
{
	int	out_size;
	int	in_size;

	out_size = get_outside_q_size(v, x, type);
	in_size = get_inside_q_size(v, type, count);	
	

bool	manage_q_tok(t_values *v, int x, char type)
{
	static int count;
	char *s;
	int	size;

	size = get_size(v, x, type, count);		//for malloc
	count++;
	return (true);
}
	








// je vais peut etre avoir besoin de savoir le nombre de quotes, non j'ai juste besoin d'un int statique je pense, c'est juste pour pas remanager 
// la meme quote quand je rerentre dans la fonction.




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
