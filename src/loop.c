/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:12:00 by adelille          #+#    #+#             */
/*   Updated: 2024/12/01 15:05:37 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	loop(void)
{
	char	*line;

	while (true)
	{
		line = prompt();
		if (!line)
			continue ;
		printf("\033[1;36m[DEBUG]\033[0m\tgot: '%s'\n", line);
		if (ft_strcmp(line, "exit") == 0)
		{
			printf("\033[1;36m[DEBUG]\033[0m\texiting\n");
			free(line);
			break ;
		}
		free(line);
	}
	return (true);
}
