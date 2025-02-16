/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:12:00 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 15:42:46 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	loop(char ***envp)
{
	bool		exit;
	char		*line;
	t_exp_list	*exp_list;

	exit = false;
	while (!exit)
	{
		line = prompt(*envp, &exit);
		if (!line)
			continue ;
		dbg(line);
		exp_list = parse(line, *envp);
		free(line);
		if (!create_file_redirection(exp_list) || !create_pipe(exp_list))
		{
			ft_lstclear((t_list **)&exp_list, exp_free);
			continue ;
		}
		exit = !exec_all_exp(exp_list, envp);
		ft_lstclear((t_list **)&exp_list, exp_free);
	}
	return (true);
}
