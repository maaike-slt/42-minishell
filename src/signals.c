/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 16:25:34 by msloot            #+#    #+#             */
/*   Updated: 2025/02/16 17:22:16 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint(int signum, siginfo_t *info, void *context)
{
	t_status	*status;

	(void)context;
	status = (t_status *)info->si_value.sival_ptr;
	*status = signum;
	dbg_number("signal status = ", *status);
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", false);
	rl_on_new_line();
	rl_redisplay();
}

struct sigaction	init_sigaction_struct(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	return (sa);
}

void	set_sigint(void)
{
	struct sigaction	sa;

	sa = init_sigaction_struct();
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &ft_sigint;
	sigaction(SIGINT, &sa, NULL);
}

void	ignore_sigint(void)
{
	struct sigaction	sa;

	sa = init_sigaction_struct();
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
}

void	set_sigquit(void)
{
	struct sigaction	sa;

	sa = init_sigaction_struct();
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}
