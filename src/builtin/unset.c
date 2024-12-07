/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:03:51 by msloot            #+#    #+#             */
/*   Updated: 2024/12/08 16:45:22 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_args *arg)
{
	size_t	i;
	ssize_t	index;

	i = 1;
	while (i < arg->argc)
	{
		index = find_env(arg->envp, arg->argv[i]);
		if (index >= 0)
			ft_2d_drop((void **)arg->envp, index);
		i++;
	}
	return (EX_OK);
}
