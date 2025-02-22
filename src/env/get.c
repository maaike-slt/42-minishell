/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:08:35 by msloot            #+#    #+#             */
/*   Updated: 2025/02/18 22:53:09 by adelille         ###   ########.fr       */
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

#ifdef TEST

bool	test_getenv(void)
{
	char	**envp;
	bool	r;

	envp = dummy_envp("VAR=42");
	r = EX_OK;
	r |= assert_str_eq("getenv VAR", ft_getenv(envp, "VAR"), "42");
	r |= assert_eq("getenv VAR index", find_env(envp, "VAR"), 0);
	r |= assert("getenv VAR not found", ft_getenv(envp, "NOT_FOUND") == NULL);
	r |= assert_eq("getenv VAR not found index",
			find_env(envp, "NOT_FOUND"), -1);
	free(envp);
	return (r);
}

#endif
