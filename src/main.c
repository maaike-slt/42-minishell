/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:45:45 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/23 21:26:02 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int sig;		// use of a global only to manage one edge case: write viable command and then ^C, bash will not execute.

int	copy_cmd_str(t_values *values)
{
	if (values->cmd_str)
	{
		values->cmd_str_b = ft_strdup(values->cmd_str);
		if (!values->cmd_str_b)
			return (-1);
		return (0);
	}
	return(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_values	values;

	values.env = envp;
	values.prev_ret_val = 0;
	(void)argc;
	(void)argv;
	set_sig_handler();			// protect	?
	while (1)
	{
		values.cmd_str = readline("minishell$ ");
		if (copy_cmd_str(&values) == -1)
			return (values.prev_ret_val);
		if (!values.cmd_str)
		{
			rl_clear_history();
			break ;
		}
		add_history(values.cmd_str);
		handle_cmd_str(&values);
		free(values.cmd_str_b);
	}
	return (values.prev_ret_val);
}
