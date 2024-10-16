/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_put_in_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:42:07 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/16 17:42:12 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	do_put_in_string(t_values *v, char *var, int *i, int size_name_var)
{
	char *expand;
	int	index;

	if (check_var_exist(v, var, &index) == false)
	{
		if (put_in_string(&v->cmd_str, "", i, size_name_var) == false)
			return (false);
		return (true);
	}
	expand = get_expand(v->env[index]);
	if (put_in_string(&v->cmd_str, expand, i, size_name_var) == false)				// i is manipulated here
	{
		free(expand);
		return (false);
	}
	free(expand);
	return (true);
}
