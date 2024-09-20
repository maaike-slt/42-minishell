/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/18 19:02:41 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_abs_path(char *s)
{
	extern	char **environ;
	char **paths;

	paths = ft_split(environ[40], ':'); 		// this is $PATH
	printf("%s\n", paths[0]);	// split isn't enough. will check if other way
	printf("%s\n", paths[1]);
	printf("%s\n", paths[2]);
	printf("%s\n", paths[3]);
	printf("%s\n", paths[4]);
	printf("%s\n", paths[5]);
	s = NULL;
	return (NULL);
}
	



int	parse(char *cmd_str)
{
	char **split;
	extern char **environ;
	char *abs_path;

	split = ft_split(cmd_str, ' ');
	abs_path = get_abs_path(split[0]);	
	execve(split[0], &split[1], environ);
	ft_free_2d((void ***)&split, ft_2d_size((const void **)split));
	return (0);
}

