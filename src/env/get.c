/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:08:35 by msloot            #+#    #+#             */
/*   Updated: 2024/12/10 20:30:12 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	envcmp(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s2[i] == '\0' && s1[i] == '=')
		return (i + 1);
	return (0);
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

char	*ft_getenv(char **envp, const char *key)
{
	size_t	i;
	size_t	path_index;

	i = 0;
	while (envp[i] != NULL)
	{
		path_index = envcmp(envp[i], key);
		if (path_index > 0)
			return (&(envp[i][path_index]));
		i++;
	}
	return (NULL);
}
// TODO: unit test