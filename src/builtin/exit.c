/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:29:17 by adelille          #+#    #+#             */
/*   Updated: 2025/02/28 18:37:00 by adelille         ###   ########.fr       */
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

static t_status	correct_overflow(const char *arg, size_t size, char sign)
{
	size_t	un;

	if (size > 20)
		return (numeric_argument_required(arg));
	if (sign)
		un = ft_atoun(&arg[1]);
	else
		un = ft_atoun(arg);
	if ((sign == '-' && un > ((size_t)LONG_MAX) + 1)
		|| (sign != '-' && un > LONG_MAX))
		return (numeric_argument_required(arg));
	return ((t_status)ft_aton(arg));
}

static t_status	exit_status(const char *arg)
{
	size_t	i;
	char	sign;

	i = 0;
	sign = '\0';
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = arg[i];
		i++;
	}
	while (arg[i] && !ft_isspace(arg[i]))
	{
		if (!ft_isdigit(arg[i]))
			return (numeric_argument_required(arg));
		i++;
	}
	return (correct_overflow(arg, i, sign));
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
