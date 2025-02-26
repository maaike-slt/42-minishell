/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:29:17 by adelille          #+#    #+#             */
/*   Updated: 2025/02/26 17:16:47 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	exit_status(const char *arg)
{
	size_t	i;
	ssize_t	n;
	char	*tmp;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] && !ft_isspace(arg[i]))
	{
		if (!ft_isdigit(arg[i]))
		{
			tmp = ft_strjoin(arg, ": numeric argument required");
			error("exit", tmp);
			free(tmp);
			return (EX_USAGE);
		}
	}
	n = ft_aton(arg);
	return ((t_status)n);
}

int	ft_exit(t_exp *exp, t_status *status)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (exp->argc > 2)
	{
		error("exit", "too many arguments");
		*status = EX_ERR;
		return (D_OKAY);
	}
	if (exp->argc == 1)
		*status = 0;
	else
		*status = exit_status(exp->argv[1]);
	dbg("👋");
	return (D_EXIT);
}
