/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:19:51 by adelille          #+#    #+#             */
/*   Updated: 2024/12/14 19:25:01 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef TEST

char	**dummy_envp(char *first)
{
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * 2);
	if (!envp)
		return (NULL);
	envp[0] = first;
	envp[1] = NULL;
	return (envp);
}

#endif
