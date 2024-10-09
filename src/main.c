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

int sig;		// use of a global only to manage one edge case: write viable command and then ^C, bash will not execute.

int	main(void)
{
	t_values	values;

	values.prev_ret_val = 0;
	set_sig_handler();			// protect	?
	while (1)
	{
		printf("%d\n", values.prev_ret_val);
		values.cmd_str = readline("minishell$ ");
		if (!values.cmd_str)
		{
			rl_clear_history();
			break ;
		}
		add_history(values.cmd_str);
		handle_cmd_str(&values);
	}
	return (0);
}
