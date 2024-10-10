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

char	*new_str(char *s)
{
	char *new;
	int	size;

	size = ft_strlen(s);
	new = malloc(sizeof(char) * (size + 3));
	ft_strcpy(new, s);
	new[size] = ' ';
	new[size + 1] = ' ';
	new[size + 2] = 0;
	return (new);
}

void	sig_c(int x)
{
	extern int sig;
	if (sig == -2)				//minishell in minishell signals
	{
		sig = -2;
		return ;
	}			
	if (sig == -1)		// everything sig == -1 is to handle signal while a bin is running in a child process, sig -1 is set in execute()
	{
		rl_replace_line("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		rl_erase_empty_line = 0;
		sig = 1;
		return ;
	}
	rl_done = 1;		// do nothing except returning readline (and print ^C in previous line, as in bash)
	sig = 1;
	x++;
}

void	sig_slash(int x)
{
	extern int sig;
	char	*temp;
	char	*new;

	if (sig == -2)				//minishell in minishell signals
	{
		sig = -2;
		return ;
	}			
	rl_erase_empty_line = 1;
	if (sig == -1)
	{	
		rl_replace_line("\n", 1);
		new = NULL;
	}
	else
	{
		temp = rl_line_buffer;	
		new = new_str(temp);
		rl_replace_line(new, 1);	// without this "^\" is printed
		free(new);
	}
	rl_on_new_line();
	rl_redisplay();
	rl_erase_empty_line = 0;
	if (sig != -1)
		rl_line_buffer[ft_strlen(temp) - 2] = 0;				// hack to have a clean buffer in the history
	rl_end -= 2;				// without this, buffer contains "  "
	sig = 2;
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
