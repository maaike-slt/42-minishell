/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 18:16:21 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/05 18:43:54 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)			// needed to have the event handler check rl_done in order to return readline on ^C
{
	return (0);
}

void	sig_c(int x)
{
	extern int sig;

	sig = 1;
	rl_done = 1;		// do nothing except returning readline (and print ^C in previous line, as in bash)
	x++;
}

void	sig_slash(int x)
{
	rl_erase_empty_line = 1;
	rl_replace_line("  ", 1);	// without this "^\" is printed
	rl_on_new_line();
	rl_redisplay();
	rl_erase_empty_line = 0;
	rl_end -= 2;				// without this, buffer contains "  "
	x++;
}

int	set_sig_handler(void)
{
	struct sigaction s_sig_c;	
	struct sigaction s_sig_slash;	

	rl_event_hook = event;		// needed to check for rl_done in signals, to return readline on ^C
	s_sig_c.sa_handler = sig_c;
	s_sig_c.sa_flags = SA_RESTART;
	s_sig_slash.sa_handler = sig_slash;
	s_sig_slash.sa_flags = SA_RESTART;
	sigemptyset(&s_sig_c.sa_mask);
	sigemptyset(&s_sig_slash.sa_mask);
	sigaction(SIGINT, &s_sig_c, NULL);
	sigaction(SIGQUIT, &s_sig_slash, NULL);
	return (0);
}
