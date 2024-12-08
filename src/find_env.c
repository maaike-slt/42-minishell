/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:08:35 by msloot            #+#    #+#             */
/*   Updated: 2024/12/07 18:46:10 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	envcmp(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s2[i] == '\0' && s1[i] == '=')
		return (true);
	return (false);
}

ssize_t	find_env(char **envp, const char *key)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (envcmp(envp[i], key))
			return (i);
		i++;
	}
	return (-1);
}

// TODO: unit test