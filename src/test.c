/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:59:04 by adelille          #+#    #+#             */
/*   Updated: 2024/12/02 21:14:41 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef TEST
#include "minishell.h"

bool	assert(const char *name, bool r)
{
	if (r)
		return (EX_OK);
	if (r)
		printf("\033[1;32m%s: OK\n\033[0m", name);
	else
		printf("\033[1;31m%s: KO\n\033[0m", name);
	return (r);
}

int main(void)
{
	bool	r;

	r = EX_OK;
	r |= test_expression_len();
	return (r);
}
#endif
