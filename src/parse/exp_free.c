/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:23:23 by adelille          #+#    #+#             */
/*   Updated: 2024/12/10 22:15:12 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_free(void *exp)
{
	t_exp	*e;

	if (!exp)
		return ;
	e = (t_exp *)exp;
	ft_2d_free((void ***)&e->argv, e->argc);
	free(e);
}
