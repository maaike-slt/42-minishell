/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:23:35 by msloot            #+#    #+#             */
/*   Updated: 2024/12/02 22:02:31 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dispatch	dispatch(t_args *arg)
{
	if (ft_strcmp(arg->argv[0], "exit") == 0)
	{
		printf("\033[1;36m[DEBUG]\033[0m\texiting\n");
		return (D_EXIT);
	}
	else
	{
		if (!builtin(arg))
			return (D_ERROR);
	}
	return (D_OKAY);
}
