/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:42:44 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 17:11:33 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef DEBUG

void	dbg(const char *str)
{
	ft_putstr_fd(DEBUG_PREFIX, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

#else

void	dbg(const char *str)
{
	(void)str;
}

#endif
