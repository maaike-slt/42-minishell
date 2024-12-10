/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:45 by msloot            #+#    #+#             */
/*   Updated: 2024/12/10 20:32:49 by msloot           ###   ########.fr       */
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
	char	*home_path;

	dbg_builtin(argc, argv);
	(void)envp;
	if (argc > 2)
		return (error(argv[0], "too many arguments"), EX_ERR);
	if (argc == 2)
		return (go(argv[1]));
	if (argc == 1)
	{
		home_path = ft_getenv(envp, "HOME");
		if (!home_path)
			return (ft_puterr("HOME not set"), EX_ERR);
		return (go(home_path));
	}
	return (go(argv[1]));
	// update pwd to the new location
}
