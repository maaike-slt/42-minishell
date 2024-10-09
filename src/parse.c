/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/05 18:48:26 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int	*sig, t_values *v)
{
	if (*sig == 1)
		v->prev_ret_val = 130;
	if (*sig == 2)
		v->prev_ret_val = 131;	// 131 set only if ^\ interrupt a binary
	*sig = 0;
}

bool	abs_path_in_values(t_values *values, char **split_str)
{
	values->abs_path = get_abs_path(values, *split_str);
	if (!values->abs_path)
	{
		ft_free_2d((void ***)&split_str, ft_2d_size((const void **)split_str));
		free(values->cmd_str);
		return (false);
	}
	return (true);
}

bool	get_struct_values(t_values *values)
{
	char	**split_str;
	extern char	**environ;

	values->env = environ;
	split_str = ft_split_whitespace(values->cmd_str);
	if (!split_str || !split_str[0])		// !split[0] otherwise segfault if cmd_str is only spaces
	{
		free(values->cmd_str);
		if (split_str)
			free(split_str);
		return (false);
	}
	if (abs_path_in_values(values, split_str) == false)
		return (false);
	values->bin_args = split_str;				// here execve accept as args the full split_str if it is valid (be careful of segfault in program with bullshit data here, the syscalls will be resilient but maybe not the program)
	return (true);
}

bool	parse(t_values *v)
{
	extern int sig;

	if (sig == 1 || sig < 0)
	{
		handle_sig(&sig, v);
		return (false);				// return here because if given "ls ^C" ls will be executed, when it shouldnt be
	}
	if (get_struct_values(v) == false)
		return (false);
	execute(v);	
	if (v->abs_path)	// should put all this in a handle_parse_exit()
	{
		if (!ft_strchr(*v->bin_args, '/'))			// this is only to free append (so "ls" or "cron", which become "/bin/ls"), otherwise abs_path is in fact *split_tr (because if line is "./a.out" and is viable, execve can use this)
			free(v->abs_path);
	}
	ft_free_2d((void ***)&v->bin_args, ft_2d_size((const void **)v->bin_args));
	free(v->cmd_str);
	if (sig)			// need to check on exit also for an edge case (if sig is caught while a bin is running, then a call to readline would fail after and also $? wouldn't be accurate)
		handle_sig(&sig, v);
	return (true);
}
