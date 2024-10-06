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

bool	abs_path_in_values(t_values *values, char **split_str)
{
	values->abs_path = get_abs_path(*split_str);
	if (!values->abs_path)
	{
		ft_free_2d((void ***)&split_str, ft_2d_size((const void **)split_str));
		free(values->cmd_str);
		return (false);
	}
	if (values->abs_path)
	{
		if (!ft_strchr(values->cmd_str, '/'))			// this is only to free append (so "ls" or "cron", which become "/bin/ls"), otherwise abs_path is in fact line (because if line is "./a.out" and is viable, execve can use this)
			free(values->abs_path);
	}
	return (true);
}

bool	get_struct_values(t_values *values)
{
	char	**split_str;

	split_str = ft_split_whitespace(values->cmd_str);
	if (!split_str || !split_str[0])		// otherwise segfault if cmd_str is only spaces
	{
		free(values->cmd_str);
		if (split_str)
			free(split_str);
		return (false);
	}
	if (abs_path_in_values(values, split_str) == false)
		return (false);
//	values->abs_path = get_abs_path(*split_str);
//	if (!values->abs_path)
//	{
//		ft_free_2d((void ***)&split_str, ft_2d_size((const void **)split_str));
//		free(values->cmd_str);
//		return (false);
//	}
//	if (values->abs_path)
//	{
//		if (!ft_strchr(values->cmd_str, '/'))			// this is only to free append (so "ls" or "cron", which become "/bin/ls"), otherwise abs_path is in fact line (because if line is "./a.out" and is viable, execve can use this)
//			free(values->abs_path);
//	}
	ft_free_2d((void ***)&split_str, ft_2d_size((const void **)split_str));
	free(values->cmd_str);
	return (true);
}
	


bool	parse(t_values *values)
{
//	char	*abs_path;
//	char	**split_s;

	if (get_struct_values(values) == false)
		return (false);
//	split_s = ft_split_whitespace(cmd_str);
//	if (!split_s || !split_s[0])		// otherwise segfault if cmd_str is only spaces
//	{
//		free(cmd_str);
//		if (split_s)
//			free(split_s);
//		return (false);
//	}
//	abs_path = get_abs_path(*split_s);
//	if (!abs_path)
//	{
//		ft_free_2d((void ***)&split_s, ft_2d_size((const void **)split_s));
//		free(cmd_str);
//		return (false);
//	}
//						// perhaps before just have a get_struct_values() ?
////	execute(values);	// put execve and getting $? in there
//	//get_args()
//	//execve(abs_path, args, environ);			// don't forget NULL terminate args
//	if (abs_path)
//	{
//		if (!ft_strchr(cmd_str, '/'))			// this is only to free append (so "ls" or "cron", which become "/bin/ls"), otherwise abs_path is in fact line (because if line is "./a.out" and is viable, execve can use this)
//			free(abs_path);
//	}
//	ft_free_2d((void ***)&split_s, ft_2d_size((const void **)split_s));
//	free(cmd_str);
	return (true);
}
