/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:19:30 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/02 15:20:53 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///	parsing environment for PATH variable ///

static	int	path_in_environ(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strnstr(environ[i], "PATH=", 5))
			break ;
		i++;
	}
	if (environ[i] == NULL)
		return (-1);
	return (i);
}

/// split PATH string into char ** to be usable ///

static char	**split_env_path(void)
{
	extern char	**environ;
	char		**split;
	char		**second;
	char		*tmp;
	int			i;

	i = path_in_environ();
	if (i == -1)
		return (NULL);
	split = ft_split(environ[i], ':');
	if (!split)
		return (NULL);
	second = ft_split(split[0], '=');
	if (!second)
	{
		ft_free_2d((void ***)&split, ft_2d_size((const void **)split));
		return (NULL);
	}
	tmp = split[0];
	split[0] = second[1];
	free(tmp);
	ft_free_2d((void ***)&second, 1);
	return (split);
}

///  getting absolute path of executable for execve() ///

char	*get_abs_path(char *executable)
{
	char	**paths;
	char	*dir;

	paths = split_env_path();
	if (!paths)
		return (NULL);
	dir = search_for_dir(paths, executable);
	if (!dir)
	{
		ft_free_2d((void ***)&paths, ft_2d_size((const void **)paths));
		return (NULL);
	}
	ft_free_2d((void ***)&paths, ft_2d_size((const void **)paths));
	return (dir);
}
