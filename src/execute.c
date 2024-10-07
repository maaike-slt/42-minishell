/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 14:39:26 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/06 14:39:41 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_values *v)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		if (execve(v->abs_path, v->bin_args, v->env) == -1)
		{
			if (v->abs_path)
			{
				if (!ft_strchr(*v->bin_args, '/'))			// all of this is the same "free" code as parse(), it is to protect everything is execve fail (the child proc would still run and mes everything)(happens is given a bin without the perms)
					free(v->abs_path);
			}
			ft_free_2d((void ***)&v->bin_args, ft_2d_size((const void **)v->bin_args));
			free(v->cmd_str);
		}
		rl_clear_history();
		exit (0);
	}
	else 
	{
		waitpid(-1, &status, 0);
		v->prev_ret_val = WEXITSTATUS(status);
	}
	return (0);
}
