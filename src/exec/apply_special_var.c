/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_special_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:52:19 by adelille          #+#    #+#             */
/*   Updated: 2025/02/23 13:40:01 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	expand_special_var(char **arg, size_t i, t_status *status)
{
	char	*tmp;

	tmp = ft_itoa(*status);
	if (!tmp)
		return (error("malloc", strerror(errno)), false);
	tmp = ft_strjoin_free(tmp, &(*arg)[i + 1], true, false);
	if (!tmp)
		return (error("malloc", strerror(errno)), false);
	*arg[i] = '\0';
	*arg = ft_strjoin_free(*arg, tmp, true, true);
	return (true);
}

bool	apply_special_var(t_exp *exp, t_status *status)
{
	size_t	arg_i;
	size_t	char_i;

	arg_i = 0;
	while (arg_i < (size_t)exp->argc)
	{
		char_i = 0;
		while (exp->argv[arg_i][char_i])
		{
			if (exp->argv[arg_i][char_i] == IR_STATUS_FLAG)
			{
				if (!expand_special_var(&(exp->argv[arg_i]), char_i, status))
					return (false);
			}
			char_i++;
		}
		arg_i++;
	}
	return (true);
}
