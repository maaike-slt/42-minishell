/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:23:23 by adelille          #+#    #+#             */
/*   Updated: 2024/12/08 18:50:32 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expression_free(void *exp)
{
	t_expression	*e;

	if (!exp)
		return ;
	e = (t_expression *)exp;
	if (e->argv)
	{
		free(e->argv);
		e->argv = NULL;
	}
	free(e);
}
