/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:25:34 by msloot            #+#    #+#             */
/*   Updated: 2025/02/26 21:27:34 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signum;

void	process_handler(int signum)
{
	g_signum = signum;
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	prompt_handler(int signum)
{
	process_handler(signum);
	rl_replace_line("", false);
	rl_on_new_line();
	rl_redisplay();
}

static struct sigaction	init_sigaction_struct(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	return (sa);
}

void	set_sigint(void (*handler)(int))
{
	struct sigaction	sa;

	sa = init_sigaction_struct();
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
}

void	set_sigquit(void (*handler)(int))
{
	struct sigaction	sa;

	sa = init_sigaction_struct();
	sa.sa_handler = handler;
	sigaction(SIGQUIT, &sa, NULL);
}
