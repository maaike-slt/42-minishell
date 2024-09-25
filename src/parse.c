/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/25 18:57:58 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_env_path(void)
{
	extern char	**environ;
	char		**split;
	char		**second;
	char		*tmp;
	size_t		i;

	i = 0;
	while (environ[i])
	{
		if (ft_strnstr(environ[i], "PATH=", 5))		// should protect for PATH=NULL or no PATH here ? yes ->segfault otherwise
			break ;
		i++;
	}
	split = ft_split(environ[i], ':');
	second = ft_split(split[0], '=');
	tmp = split[0];
	split[0] = second[1];
	free(tmp);
	ft_free_2d((void ***)&second, 1);
	return (split);
}

// has to work with ../../../bin/ls
// ~/../../bin/ls 
// ./ls	 (if current dir is /bin)
// ls	(if current dir is /bin)
// what about current directory ? if we cd to /bin or any dir we have to be able to execute a bin there. So in path get also the current dir
// check man about paths

static char	*get_abs_path(char *s)
{
	char	**paths;
	char *result;

	paths = split_env_path();
	result = search_for_dir(paths, s)
	//get_args()
	s = 0;
	return (NULL);
}

static bool	split_prompt(char *line)
{
	char	**sep_prompt;
	size_t	i;

	sep_prompt = ft_split_whitespace(line);
	if (!sep_prompt)
		return (false);
	return (true);
}

bool	parse(char *cmd_str)
{
	char	*line;

	line = readline(cmd_str);
	if (!line)
		return (false);
	add_history(line);
	if (!split_prompt(line))
		return (false);
	get_abs_path(cmd_str);
	//execve(get_abs_path(cmd_str), get_args(cmd_str), environ);		// be careful to always NULL-terminate get_args 
	free(line);
	return (true);
}
