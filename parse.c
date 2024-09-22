/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/20 19:26:41 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_env_path(void)			// check for NULL string or error here ?
{
	extern char	**environ;
	char		**split;
	char		**second;
	char		*temp;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strnstr(environ[i], "PATH=", 5))
			break ;
		i++;
	}
	split = ft_split(environ[i], ':');
	second = ft_split(split[0], '=');
	temp = split[0];
	split[0] = second[1];
	free(temp);
	ft_free_2d((void ***)&second, 1);
	return (split);
}

char	*get_abs_path(char *s)
{
	char	**paths;

	paths = split_env_path();
	s = 0;
	return (NULL);
}

int	parse(char *cmd_str)
{
	get_abs_path(cmd_str);
	//execve(get_abs_path(cmd_str), get_args(cmd_str), environ);		// be careful to always NULL-terminate get_args 
	return (0);
}
