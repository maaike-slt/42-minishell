/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:03:51 by msloot            #+#    #+#             */
/*   Updated: 2024/12/05 19:57:51 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_args *arg)
{
	ssize_t	index;

	// TODO check for right number of args
	index = find_env(arg->envp, arg->argv[1]);
	if (index != -1)
	{
		// handle not found
		return (0);	// must be the same return as in `bash`
	}
}
