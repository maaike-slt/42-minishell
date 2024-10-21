/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:28:34 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/17 15:28:37 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//bool	isquote(char *s)
//{
//	int	i;
//
//	i = 0;
//	while (s[i])
//	{
//		if (s[i] == '\'' || s[i] == '\"')
//			return (true);
//		i++;
//	}
//	return (false);
//}

int	count_q_expand(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

int	put_in_counter(t_values *v, char *s, int *i, int *tab)
{
	char *var;
	int	index;
	char *expand;
	int		size_name_var;
	
	var = get_var(&s[1], &size_name_var);
	if (!var)
		return (false);
	if (check_var_exist(v, var, &index) == false)
	{
		(*i)++;
		return (true);				// je return true pour que le loop dans la func davant continue, false only for malloc fail
	}
	expand = get_expand(v->env[index]);
	if (!expand)
		return (false);
	*tab += count_q_expand(expand);
	free (expand);
	return (true);
}

bool	allocate_tab(t_values *v, int **tab)
{
	int	i;
	int	tab_counter;

	i = 0;
	tab_counter = 1;		// on va faire un tab avec deux cases avant et après chaque token de quote, mem quand ya pas denv var, avec //// je pense que j'ai pas besoin de term le tab par -1
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')			// ouai mais la je dois aussi compter d'une maniere les quotes, pour savoir combien de int dans le tableau
		{
			quote_redpip(&v->cmd_str_b[i], &i);
			tab_counter++;
			continue ;
		}
		i++;
	}
	*tab = malloc(sizeof(int) * (tab_counter + 1));
	if (!(*tab))
		return (false);
	ft_bzero(*tab, sizeof(int) * tab_counter);
	(*tab)[tab_counter] = -1;
	return (true);
}

bool	get_counter(t_values *v, int **tab)
{
	int	i;
	int	ind_tab;

	i = 0;
	ind_tab = 0;
	if (allocate_tab(v, tab) == false)
		return (false);
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')			// ouai mais la je dois aussi compter d'une maniere les quotes, pour savoir combien de int dans le tableau
		{
			quote_redpip(&v->cmd_str_b[i], &i);
			ind_tab++;
			continue ;
		}
		if (v->cmd_str_b[i] == '$')			//je dois juste regarder si ya des quotes dans les env var et leurs nombres
		{
			if (put_in_counter(v, &v->cmd_str_b[i], &i, &(*tab)[ind_tab]) == false)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	do_quotes(t_values *values)
{
	int	*tab;
	int	i = 0;

	tab = NULL;
	if (values->isquote == 0)
		return (true);
	if (get_counter(values, &tab) == false)
		return (false);
	while (tab[i] != -1)
	{	
		printf("%d\n", tab[i]);
		i++;
	}
	free(tab);
	values->isquote = 0;
	return (true);
}






//peut etre un truc que je peux faire pour ne pas arriver sur des quotes qui ont été expand, c'est de parcourir la cmd_str originale (je sais plus si je l'ai toujours, faut que je check, je crois pas)
//et lorsque  je trouve un dollar je peux avancer du nombre de char de la env var ? si elle est valide etc ?
//Ouai nan c'est pas évident car is ya des espaces dedans ils existent plus etc, je me dit que plutot je dois voir dans string originial et checker si tous les char correspondent entre la split-str
//et la cmd_str (originale) et si j'avance jusqu'à la quotes c'est que c'est validé et du coup je peux commencer le travail de management des tokens.


// ou alors je peux peutetre faire un trucc zarb, genre je split la strings quand ya pas les quotes, et j'alloue avec

//ouai je pourrais faire ça, genre je fais un split whitespace sur un portion de la string, puis ensuite sur.

//Non je pense que c'est moins prone aux bugs de faire ce que je voulais faire de base, aussi je pense que juste copier ce qu'il y a entre les quotes sur la string originale, ensuite ya plus qu'a free
//ce qu'il reste etc..

//Essayons ça d'abord.


//ouai ce que je peux faire c'est comme je sais que les quotes sont viables si ca vient jusqici, je peux juste regarder
// ouai non en fait j'ai besoin de checker si l'interieur du token correspond à la string entre les quotes, ouai mais avec cette maniere de faire, ça veut dire que pourrais faire péter le programme
//si je fais une var d'env qui est exactement pareil que le token que j'essaie de checker, ou alors ce que je peux faire c'est en parsant la string, si je vois que ya des env var, avec des quotes dedans,
//je skip le nombre de quote dans l'env var, genre je fais un counter etc. et donc après je peux aller dans les token de split et meme pas regarder ce qu'il y a dedans, juste faire avec le counter, et ensuite
//checker ce que je dois copier dans le char * du split et voila, ainsi que déplacer et free les tokens jusqu'à celui qui a la deuxieme quote, et après on repart pour un tour.
// de toute maniere je pense que j'ai déjà toutes les fonctions nécessaires pour gérer le counter de quotes si yen a dans les env var




// ouai je devrais parser dans les split token, c'est juste que je dois juste regarder une première fois dans la string originale si ya des env var et si ya des quotes dedans pour les skip dans les tokens




// ouai je peux faire quelque chose comme genre alloc une struc, malloc un tableau d'int pour chaque fois que je croise un dollar et après ce dollar skip le int du tableau nombre de quote après dans les tokens,
// et si je fais ça je devrais arriver a la premiere quote a gérer.

// non j'ai meme pas besoin de ça, je peux juste compter le nombre a ignorer et puis voila, pas besoin de plus d'informations


// ouai je suis sur que c'est pas possible d'avoir des quotes dans les noms des var, alors que peux parser comme un porc avec juste les quotes.







// le truc que je peux faire aussi c'est de compter si lorsque je démarre par des quotes siA


// ouai si je fais un tableau, genre le nombre de quotes que je dois skip etc.. je peux faire quelque chose du genre une case 0 si jamais j'arrive a une quote viable sans quote dans les var env, puis 3 si ya 
// 3 quotes dans les var env etc.., et lorsque je passe parmis les quotes je fais ça comme ça, je regarde avec le compteur et le tableau si je dois ignorer ou pas la quote. Ouai je pense que ça va fonctionner.
// par contre du coup je devrais faire une first pass sur le fait de pouvoir malloc le bon nombre d'int dans le tableau etc..
