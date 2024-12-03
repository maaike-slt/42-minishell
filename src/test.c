/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:59:04 by adelille          #+#    #+#             */
/*   Updated: 2024/12/03 21:24:35 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef TEST
#include "minishell.h"

bool	assert(const char *name, bool r)
{
	if (r)
		return (EX_OK);
	ft_putstr_fd("\033[1;31m[KO]:\033[33m ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("\033[0m\n", STDERR_FILENO);
	return (r);
}

bool	assert_eq(const char *name, ssize_t got, ssize_t expected)
{
	if (got == expected)
		return (EX_OK);
	ft_putstr_fd("\033[1;31m[KO]:\033[33m ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("\033[0m\n\t\033[31mgot:\033[0m      ", STDERR_FILENO);
	ft_putnbr_fd(got, STDERR_FILENO);
	ft_putstr_fd("\n\t\033[32mexpected:\033[0m ", STDERR_FILENO);
	ft_putnbr_fd(expected, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (EX_ERR);
}

int main(void)
{
	bool	r;

	r = EX_OK;
	r |= test_expression_len();
	if (r == EX_OK)
		ft_putstr_fd("\033[1;32m[OK]\n\033[0m", 1);
	return (r);
}
#endif
