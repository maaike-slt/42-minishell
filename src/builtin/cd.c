/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:45 by msloot            #+#    #+#             */
/*   Updated: 2024/12/02 22:15:31 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(t_args *arg)
{
	int	ret;

	ret = 0;
	if (arg->argc > 2)
		return (error(arg->argv[0], "too many arguments"), EX_ERR);
	if (arg->argc == 1)
		// direct current position to HOME
	ret = chdir(arg->argv[1]);
	if (ret == -1)
		return (perror(arg->argv[0]), EX_ERR);
	return (EX_OK);
	// update pwd to the new location
}
