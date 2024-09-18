/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:05:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/18 18:42:08 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///char	*get_abs_path(char *s)
///{
///	extern	char **environ;

	



int	parse(char *cmd_str)
{
	char **split;
	extern char **environ;
	//char *abs_path;

	split = ft_split(cmd_str, ' ');
//	abs_path = get_abs_path(split[0]);	
	execve(split[0], &split[1], environ);
	ft_free_2d((void ***)&split, ft_2d_size((const void **)split));
	return (0);
}

