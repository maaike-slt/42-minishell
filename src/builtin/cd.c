/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:45 by msloot            #+#    #+#             */
/*   Updated: 2024/12/09 22:25:55 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go(const char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
		return (perror("cd"), EX_ERR);
	return (EX_OK);
}

int	cd(int argc, char **argv, char **envp)
{
	int	ret;

	dbg_builtin(argc, argv);
	(void)envp;
	ret = 0;
	if (argc > 2)
		return (error(argv[0], "too many arguments"), EX_ERR);
	if (argc == 2)
		return (go(argv[1]));
	if (argc == 1)
	{

		// direct current position to HOME
	}
	return (go(argv[1]));
	// update pwd to the new location
}
