/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:52 by msloot            #+#    #+#             */
/*   Updated: 2024/12/11 20:27:17 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef TEST

// TODO TOMORROW: export builtin

int	main(int argc, char **argv, char **envp)
{
	char	**envp_cpy;

	ft_putstr("Hello, World!\n");
	envp_cpy = envdup(envp);
	if (!envp_cpy)
		return (1);
	(void)argc;
	(void)argv;
	init_signals();
	loop(envp_cpy);
	rl_clear_history();
	return (0);
}

#endif
