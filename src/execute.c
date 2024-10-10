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
	extern int sig;

	pid = fork();
	if (pid == -1)		// check this for potential mistakes, I did this quickly without trying to have robust code.
		return (0);
	else if (pid == 0)
	{
		if (execve(v->abs_path, v->split_str, v->env) == -1)
		{
			if (v->abs_path)
			{
				if (!ft_strchr(*v->split_str, '/'))			// all of this is the same "free" code as parse(), it is to protect everything is execve fail (the child proc would still run and mes everything)(happens is given a bin without the perms)
					free(v->abs_path);
			}
			ft_free_2d((void ***)&v->split_str, ft_2d_size((const void **)v->split_str));
			free(v->cmd_str);
		}
		rl_clear_history();
		exit (0);
	}
	else 
	{
		sig = -1;		// for signals special cases functions in order to manage cat<enter><signal> adequately				// when minishell in minishell, set to -2 and handle differently signals to have right behaviour ?
		waitpid(-1, &status, 0);
		v->prev_ret_val = WEXITSTATUS(status);
	}
	return (0);
}
