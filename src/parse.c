/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/05 18:48:26 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parse(char *cmd_str)
{
	char	*abs_path;
	char	**split_s;

	add_history(cmd_str);		// maybe check if(!(*cmd_str)) in order not to add it in the history
	split_s = ft_split_whitespace(cmd_str);
	if (!split_s || !split_s[0])		// otherwise segfault if cmd_str is only spaces
	{
		free(cmd_str);
		if (split_s)
			free(split_s);
		return (false);
	}
	abs_path = get_abs_path(*split_s);
	if (!abs_path)
	{
		ft_free_2d((void ***)&split_s, ft_2d_size((const void **)split_s));
		free(cmd_str);
		return (false);
	}
	//get_args()
	//execve(abs_path, args, environ);			// don't forget NULL terminate args
	if (abs_path)
	{
		if (!ft_strchr(cmd_str, '/'))			// this is only to free append (so "ls" or "cron", which become "/bin/ls"), otherwise abs_path is in fact line (because if line is "./a.out" and is viable, execve can use this)
			free(abs_path);
	}
	ft_free_2d((void ***)&split_s, ft_2d_size((const void **)split_s));
	free(cmd_str);
	return (true);
}
