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

bool	do_quote(t_values *values)
{
	check_pos







peut etre un truc que je peux faire pour ne pas arriver sur des quotes qui ont été expand, c'est de parcourir la cmd_str originale (je sais plus si je l'ai toujours, faut que je check, je crois pas)
et lorsque  je trouve un dollar je peux avancer du nombre de char de la env var ? si elle est valide etc ?
Ouai nan c'est pas évident car is ya des espaces dedans ils existent plus etc, je me dit que plutot je dois voir dans string originial et checker si tous les char correspondent entre la split-str
et la cmd_str (originale) et si j'avance jusqu'à la quotes c'est que c'est validé et du coup je peux commencer le travail de management des tokens.


	
