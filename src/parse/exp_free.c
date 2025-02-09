/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:23:23 by adelille          #+#    #+#             */
/*   Updated: 2025/02/09 14:09:02 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_free(void *exp)
{
	t_exp	*e;

	if (!exp)
		return ;
	e = (t_exp *)exp;
	if (e->infd > STDERR_FILENO)
		close(e->infd);
	if (e->outfd > STDERR_FILENO)
		close(e->outfd);
	ft_2d_free((void ***)&e->argv, e->argc);
	free(e);
}
