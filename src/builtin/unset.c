/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:03:51 by msloot            #+#    #+#             */
/*   Updated: 2024/12/09 22:18:22 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(int argc, char **argv, char **envp)
{
	size_t	i;
	ssize_t	index;

	dbg_builtin(argc, argv);
	i = 1;
	while (i < (size_t)argc)
	{
		index = find_env(envp, argv[i]);
		if (index >= 0)
			ft_2d_drop((void **)envp, index);
		i++;
	}
	return (EX_OK);
}
