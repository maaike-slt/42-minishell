/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_match.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:36:38 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/07 18:36:38 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check(t_values *values, char *path)
{
	struct stat s_stat;

	if (!path)
		return (NULL);
	stat(path, &s_stat);		// protect ?
	if (!S_ISREG(s_stat.st_mode))				// test avec des print lol
	{
		values->prev_ret_val = 126;
		return (NULL);
	}
	if (access(path, X_OK) == -1)
	{
		values->prev_ret_val = 126;
		return (NULL);
	}
	return (path);
}
