/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:45 by msloot            #+#    #+#             */
/*   Updated: 2024/12/11 21:14:22 by adelille         ###   ########.fr       */
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
	if (argc > 2)
		return (error(argv[0], "too many arguments"), EX_ERR);
	if (argc == 2)
		return (go(argv[1]));
	home_path = ft_getenv(envp, "HOME");
	if (!home_path)
		return (error("cd", "HOME not set"), EX_ERR);
	return (go(home_path));
	// TODO TOMORROW: update PWD
	// TODO TOMORROW: update OLDPWD
	// TODO TOMORROW: make `cd -` work like `cd` in `bash`
}
