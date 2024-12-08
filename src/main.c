/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:52 by msloot            #+#    #+#             */
/*   Updated: 2024/12/08 16:46:30 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef TEST
int	main(int argc, char **argv, char **envp)
{
	char	**envp_cpy;

	envp_cpy = envdup(envp);
	(void)argc;
	(void)argv;
	ft_putstr("Hello, World!\n");
	init_signals();
	loop(envp_cpy);
	rl_clear_history();
	return (0);
}
#endif
