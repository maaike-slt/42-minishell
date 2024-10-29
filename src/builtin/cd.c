/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:45 by msloot            #+#    #+#             */
/*   Updated: 2024/10/29 18:49:41 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(size_t argc, char **argv, char **envp)
{
	int	ret;

	if (argc != 2)
		return (EX_ERR);
	ret = chdir(argv[1]);
	if (ret == -1)
		return (EX_ERR); // will need to replace by minishell error later
	return (EX_OK);
	// update pwd to the new location
	(void)envp; // compile
}
