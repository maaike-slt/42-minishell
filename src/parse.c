/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/25 19:44:08 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_in_environ(void)
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

static char	*get_abs_path(char *executable)
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

static bool	split_prompt(char *line)
{
	char	**sep_prompt;
	//size_t	i;

	sep_prompt = ft_split_whitespace(line);
	if (!sep_prompt)
		return (false);
	ft_free_2d((void ***)&sep_prompt, ft_2d_size((const void **)sep_prompt));		// added this to silent valgrind
	return (true);
}

bool	parse(char *prompt)
{
	char	*line;
	char	*abs_path;

	line = readline(prompt);
	if (!line)
		return (false);
	add_history(line);
	if (!split_prompt(line))
		return (false);
	abs_path = get_abs_path(line);
	if (!abs_path)
	{
		free(line);
		rl_clear_history();
		return (false);
	}
	//get_args()
	//execve(abs_path, args, environ);
	if (abs_path)
	{
		if (!ft_strchr(line, '/'))			// this is only to free append (so "ls" or "cron", which become "/bin/ls"), otherwise abs_path is in fact line (because if line is "./a.out" and is viable, execve can use this)
			free(abs_path);
	}
	free(line);
	rl_clear_history();
	return (true);
}
