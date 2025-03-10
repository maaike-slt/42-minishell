/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:42:45 by msloot            #+#    #+#             */
/*   Updated: 2025/02/18 23:19:24 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	go(const char *path, char ***envp)
{
	int		ret;
	char	*old_pwd;
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (ft_strcmp(path, "-") == 0)
	{
		old_pwd = ft_getenv(*envp, "OLDPWD");
		if (!old_pwd)
			return (free(current_pwd), error("cd", "OLDPWD not set"), EX_ERR);
		ret = chdir(old_pwd);
		ft_putendl_fd(old_pwd, STDOUT_FILENO);
	}
	else
		ret = chdir(path);
	if (ret == -1)
		return (free(current_pwd), error("cd", strerror(errno)), EX_ERR);
	if (current_pwd)
		ft_setenv(envp, "OLDPWD", current_pwd);
	free(current_pwd);
	current_pwd = getcwd(NULL, 0);
	if (current_pwd)
		ft_setenv(envp, "PWD", current_pwd);
	free(current_pwd);
	return (EX_OK);
}

int	cd(int argc, char **argv, char ***envp)
{
	char	*home_path;

	dbg_builtin(argc, argv);
	if (argc > 2)
		return (error(argv[0], "too many arguments"), EX_ERR);
	if (argc == 2 && ft_strcmp(argv[1], "--") != 0)
		return (go(argv[1], envp));
	home_path = ft_getenv(*envp, "HOME");
	if (!home_path)
		return (error("cd", "HOME not set"), EX_ERR);
	if (home_path[0] == '\0')
		return (EX_OK);
	return (go(home_path, envp));
}
