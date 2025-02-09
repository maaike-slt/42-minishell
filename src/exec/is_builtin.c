/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:02:47 by adelille          #+#    #+#             */
/*   Updated: 2025/02/09 16:30:08 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_in_list(const char *cmd, const char *list[BUILTIN_COUNT])
{
	size_t	i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ft_strcmp(cmd, list[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

bool	is_builtin(const char *cmd)
{
	return (is_in_list(cmd, (const char *[]){ "cd", "echo", "env", "unset", "export", "pwd", NULL }));
}
