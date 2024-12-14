/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:06:13 by msloot            #+#    #+#             */
/*   Updated: 2024/12/14 19:34:45 by msloot           ###   ########.fr       */
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
