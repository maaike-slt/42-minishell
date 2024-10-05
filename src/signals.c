/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:16:21 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/05 18:16:35 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_c(int x)
{
	rl_done = 1;
	x++;
}

void	sig_slash(int x)
{
	rl_erase_empty_line = 1;
	rl_replace_line("  ", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_erase_empty_line = 0;
	rl_end -= 2;
	x++;
}

int	set_sig_handler(t_signals *signals)
{
	signals->sig_c.sa_handler = sig_c;
	signals->sig_c.sa_flags = SA_RESTART;
	signals->sig_slash.sa_handler = sig_slash;
	signals->sig_slash.sa_flags = SA_RESTART;
	sigemptyset(&signals->sig_c.sa_mask);
	sigemptyset(&signals->sig_slash.sa_mask);
	sigaction(SIGINT, &signals->sig_c, NULL);
	sigaction(SIGQUIT, &signals->sig_slash, NULL);
	return (0);
}
