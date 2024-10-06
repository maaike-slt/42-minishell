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

int	execute(t_values *values)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
		return (0);
	else if (pid == 0)
	{
		execve(values->abs_path, values->bin_args, values->env);
	}
	else 
	{
		waitpid(-1, &status, 0);			// je sais pas pq mais -pid ça marchait pas, a checker				// do way more testing for the fork infra, to see if something can fail, and edge cases
		values->prev_ret_val = WEXITSTATUS(status);
		printf("%d\n", values->prev_ret_val);
	}
	return (0);
}
