/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:21:47 by adelille          #+#    #+#             */
/*   Updated: 2025/02/23 19:08:48 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_dir(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (false);
	return (S_ISDIR(st.st_mode));
}

bool	prepare_bin(t_exp *exp, t_status *status, char **envp)
{
	char	*path;

	path = find_bin_path(exp->argv[0], envp);
	if (exp->argv[0][0] == '\0' || path == NULL)
	{
		free(path);
		error(exp->argv[0], "command not found");
		*status = EX_NOTFOUND;
		return (false);
	}
	if (access(path, X_OK) != 0 || is_dir(path))
	{
		free(path);
		error(exp->argv[0], "permission denied");
		*status = EX_PERMDENIED;
		return (false);
	}
	free(exp->argv[0]);
	exp->argv[0] = path;
	return (true);
}
