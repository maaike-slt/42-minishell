/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:29:17 by adelille          #+#    #+#             */
/*   Updated: 2025/02/26 17:23:32 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	numeric_argument_required(const char *arg)
{
	char	*tmp;

	tmp = ft_strjoin(arg, ": numeric argument required");
	error("exit", tmp);
	free(tmp);
	return (EX_USAGE);
}

static t_status	exit_status(const char *arg)
{
	size_t	i;
	ssize_t	n;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i] && !ft_isspace(arg[i]))
	{
		if (!ft_isdigit(arg[i]))
			return (numeric_argument_required(arg));
		i++;
	}
	n = ft_aton(arg);
	if (ft_strlen(arg) > 10 || (n < 0 && ft_strlen(arg) > 11))
		return (numeric_argument_required(arg));
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
