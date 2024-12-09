/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:45 by msloot            #+#    #+#             */
/*   Updated: 2024/12/09 21:42:08 by adelille         ###   ########.fr       */
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
	ret = chdir(argv[1]);
	if (ret == -1)
		return (perror(argv[0]), EX_ERR);
	return (EX_OK);
	// update pwd to the new location
}
