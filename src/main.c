/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:45:45 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/05 18:43:54 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*cmd_str;
	t_signals	signals;

	rl_event_hook = event;		// needed to check for rl_done in signals, to return readline on ^C
	set_sig_handler(&signals);
	while (1)
	{
		cmd_str = readline("minishell$ ");
		if (!cmd_str)
		{
			rl_clear_history();
			break ;
		}
		parse(cmd_str);
	}
	return (0);
}
