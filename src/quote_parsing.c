/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:25:05 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/25 17:47:47 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	pass_check(char c, int *tab, int *z)
{
	if (c == '\'' || c == '\"')
	{
		if (*tab == 0)
		{
			(*z)++;
			return (false);
		}
		else
		{
			(*tab)--;
			return (true);
		}
	}
	return (true);
}

static void	init_count(int *count)
{
	count['\''] = 0;
	count['\"'] = 0;
}

bool	quote_parsing(t_values *v, int	*tab)		// here i need to do a struct with count to have count->single or something like this
{
	int	x;
	int	y;
	int	z;
	int	count[50];
	char type;

	x = 0;
	z = 0;
	init_count(count);
	while (v->split_str[x])
	{
		y = 0;
		while (v->split_str[x][y])
		{
			if (pass_check(v->split_str[x][y], &tab[z], &z)	== false)
			{
				type = v->split_str[x][y];
				if (manage_q_tok(v, x, v->split_str[x][y], count) == false)
					return (false);
				(count[(int)type])++;							// je peux peut etre faire une fonction ici pour incrémenter le bon type, ça prendrais qu'une seule ligne
				break ;
			}
			y++;
		}
		x++;
	}
	return (true);
}





// ouai non en fait ya pas besoin de checker pour la deuxieme quote, on fera la cuisine sur exit du managing de char * de split, genre je fais ma copie, puis
// je free les split jusqu' l'autre quote du meme type et puis on continue



// ce qu'il faudrait c'est que lorsque j'arrive au split que je dois manager, je devrais faire en sorte en revenant dans la boucle que je continue juste dans
// split d'après, meme si je suis au milieu d'un split ou ya une quote, car normalement j'aurais managé tout ça. 
