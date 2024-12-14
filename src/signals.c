/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:25:34 by msloot            #+#    #+#             */
/*   Updated: 2024/12/14 19:32:00 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO TOMORROW: make readline exit on ctrl+d (SIGQUIT)

static void	ft_sigint(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	ft_putstr_fd("\n", 1);
	/* rl_replace_line("", 0); */
	/* rl_on_new_line(); */
	/* rl_redisplay(); */
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
