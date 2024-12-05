/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:38:29 by msloot            #+#    #+#             */
/*   Updated: 2024/12/05 22:08:45 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_newline(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] != '-')
		return (false);
	i++;
	if (str[i] != 'n')
		return (false);
	i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static void	write_echo(int argc, char **argv)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (i < argc && check_newline(argv[i]))
	{
		newline = false;
		i++;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i != argc - 1)
			ft_putchar(' ');
		i++;
	}
	if (newline)
		(void)write(1, "\n", 1);
}

int	echo(t_args *arg)
{
	write_echo(arg->argc, arg->argv);
	return (EX_OK);
}
