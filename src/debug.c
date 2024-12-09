/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:42:44 by adelille          #+#    #+#             */
/*   Updated: 2024/12/09 22:22:18 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef DEBUG

void	dbg(const char *str)
{
	ft_putstr_fd("\033[1;36m[DEBUG]\033[0m\t", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

void	dbg_builtin(int argc, char **argv)
{
	size_t	i;

	ft_putstr_fd("\033[1;36m[DEBUG]\033[0m\t", STDERR_FILENO);
	ft_putstr_fd("\033[1;35m", STDERR_FILENO);
	ft_putstr_fd(argv[0], STDERR_FILENO);
	ft_putstr_fd(
		"\033[0m:\n\033[1;36m  - \033[0m\033[1margc\033[0m = \033[34m",
		STDERR_FILENO);
	ft_putnbr_fd(argc, STDERR_FILENO);
	ft_putstr_fd("\033[0m\n", STDERR_FILENO);
	i = 0;
	while (i < (size_t)argc)
	{
		ft_putstr_fd(
			"\033[1;36m  - \033[0m\033[1margv[\033[0m\033[34m", STDERR_FILENO);
		ft_putnbr_fd(i, STDERR_FILENO);
		ft_putstr_fd("\033[0m\033[1m]\033[0m = \033[32m", STDERR_FILENO);
		ft_putendl_fd(argv[i], STDERR_FILENO);
		i++;
	}
	ft_putstr_fd("\033[0m", STDERR_FILENO);
}

#else

void	dbg(const char *str)
{
	(void)str;
}

void	dbg_builtin(const char *builtin, int argc, char **argv)
{
	(void)builtin;
	(void)argc;
	(void)argv;
}

#endif
