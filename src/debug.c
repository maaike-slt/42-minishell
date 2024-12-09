/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:42:44 by adelille          #+#    #+#             */
/*   Updated: 2024/12/09 22:03:48 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dbg(const char *str)
{
	#ifdef DEBUG
		ft_putstr_fd("\033[1;36m[DEBUG]\033[0m\t", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
	#else
		(void)str;
	#endif
}

void	dbg_builtin(const char *builtin, int argc, char **argv)
{
	#ifdef DEBUG
		ft_putstr_fd("\033[1;36m[DEBUG]\033[0m\t", STDERR_FILENO);
		ft_putstr_fd("\033[1;35m", STDERR_FILENO);
		ft_putstr_fd(builtin, STDERR_FILENO);
		ft_putstr_fd("\033[0m:\n\033[1;36m  - \033[0m\033[1margc = ", STDERR_FILENO);
		ft_putnbr_fd(argc, STDERR_FILENO);
		ft_putendl_fd(" arguments", STDERR_FILENO);
		ft_putstr_fd("\033[1;36m[DEBUG]\033[0m\t", STDERR_FILENO);
		ft_putstr_fd("Arguments are: ", STDERR_FILENO);
		ft_puttab_fd(argv, STDERR_FILENO);
	#else
		(void)builtin;
		(void)argc;
		(void)argv;
	#endif
}
