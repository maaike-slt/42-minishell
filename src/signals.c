/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:25:34 by msloot            #+#    #+#             */
/*   Updated: 2025/02/16 15:46:26 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO TOMORROW: make readline exit on ctrl+d (SIGQUIT)

static void	ft_sigint(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", false);
	rl_on_new_line();
	rl_redisplay();
}

void	init_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_flags = SA_RESTART;
	sa_int.sa_sigaction = &ft_sigint;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_flags = SA_RESTART;
	sa_int.sa_sigaction = NULL;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
