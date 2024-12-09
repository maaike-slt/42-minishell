/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:23:23 by adelille          #+#    #+#             */
/*   Updated: 2024/12/09 22:00:27 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exp_free(void *exp)
{
	t_exp	*e;

	if (!exp)
		return ;
	e = (t_exp *)exp;
	if (e->argv)
	{
		free(e->argv);
		e->argv = NULL;
	}
	free(e);
}
