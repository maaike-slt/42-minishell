/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:42:44 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 17:11:11 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef DEBUG

void	dbg_number(const char *prefix, ssize_t nbr)
{
	ft_putstr_fd(DEBUG_PREFIX, STDERR_FILENO);
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd("\033[0m\033[1;34m", STDERR_FILENO);
	ft_putnbr_fd(nbr, STDERR_FILENO);
	ft_putstr_fd("\033[0m\n", STDERR_FILENO);
}

#else

void	dbg_number(const char *prefix, ssize_t nbr)
{
	(void)prefix;
	(void)nbr;
}

#endif
