/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/02 15:20:52 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
