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
	t_values	values;

	set_sig_handler();
	while (1)
	{
		values.cmd_str = readline("minishell$ ");
		if (!values.cmd_str)
		{
			rl_clear_history();
			break ;
		}
		add_history(values.cmd_str);
		parse(&values);
	}
	return (0);
}
