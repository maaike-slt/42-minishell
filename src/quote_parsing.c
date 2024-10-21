/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:25:05 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/21 16:25:07 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_pass(char c, int *tab, int *z)
{
	
	if (c == '\'' || c == '\"')
	{
		if (*tab == 0)			// ouai la ya un probleme ici, je dois aller a l'autre quote somehow
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

bool	quote_parsing(t_values *v, int	*tab)
{
	int	x;
	int	y;
	int	z; 

	x = 0;
	z = 0;
	while(v->split_str[x])
	{
		y = 0;
		while(v->split_str[x][y])
		{
			if (check_if_pass(v->split_str[x][y], &tab[z], &z)	== false)			//ouai ici je vais de voir manipuler les indices dans les fonctions je pense
			{
				printf("%s\n", &v->split_str[x][y]);
//				if (manage_q_tok(v, x, v->split_str[x][y]) == false)
//					return (false);
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
