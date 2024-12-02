/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:12:00 by adelille          #+#    #+#             */
/*   Updated: 2024/12/02 20:15:23 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_args	tmp_parsing(const char *line, char **envp)
{
	t_args	ret;

	ret.argv = ft_split_whitespace(line);
	ret.argc = ft_2d_size((const void **)ret.argv);
	ret.envp = envp;
	return (ret);
}

bool	loop(char **envp)
{
	char		*line;
	t_args		arg;
	t_dispatch	dispatch_ret;

	while (true)
	{
		line = prompt();
		if (!line)
			continue ;
		printf("\033[1;36m[DEBUG]\033[0m\tgot: '%s'\n", line);
		// TODO: parsing
		arg = tmp_parsing(line, envp);
		free(line);
		dispatch_ret = dispatch(&arg);
		if (dispatch_ret == D_EXIT)
			break ;
	}
	return (true);
}
