/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:21:47 by adelille          #+#    #+#             */
/*   Updated: 2025/02/17 19:17:13 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	prepare_bin(t_exp *exp, t_status *status, char **envp)
{
	char	*path;

	path = find_bin_path(exp->argv[0], envp);
	if (path == NULL)
	{
		free(path);
		error(exp->argv[0], "command not found");
		*status = EX_NOTFOUND;
		return (false);
	}
	if (access(path, X_OK) != 0)
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
