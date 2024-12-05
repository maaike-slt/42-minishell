/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:52 by msloot            #+#    #+#             */
/*   Updated: 2024/12/05 21:57:17 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef TEST
int	main(void)
{
	ft_putstr("Hello, World!\n");
	init_signals();
	loop();
	rl_clear_history();
	return (0);
}
#endif
