/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:15:53 by adelille          #+#    #+#             */
/*   Updated: 2024/12/14 16:32:32 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_single_path(const char *dir, const char *cmd)
{
	char	*path;

	path = ft_strdup(dir);
	if (!path)
		return (NULL);
	path = ft_strpush(&path, '/');
	if (!path)
		return (NULL);
	path = ft_strjoin_free(path, (char *)cmd, true, false);
	if (!path)
		return (NULL);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*find_bin_path(const char *cmd, char **envp)
{
	size_t	i;
	char	*path;
	char	**paths;

	path = ft_getenv(envp, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split_any_of(path, ":");
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		path = check_single_path(paths[i], cmd);
		if (path != NULL)
		{
			ft_2d_free((void ***)&paths, ft_2d_size((const void **)paths));
			return (path);
		}
		i++;
	}
	ft_2d_free((void ***)&paths, ft_2d_size((const void **)paths));
	return (NULL);
}
