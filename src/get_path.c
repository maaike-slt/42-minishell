/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:03:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/25 19:03:12 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_for_dir(char	*env_paths, char *executablej)			// don't forget cur dir
{
	DIR *directory;
	struct dirent *dirent;
	int	i;

	i = 0;
	directory =	opendir("env_paths[i]");
	dirent = readdir(env_paths[0]);

	while(dirent)		// this loop is not finished, need to loop in all the paths also
	{
		if (ft_strcmp(exexecutable, dirent->d_name))		// find the right function in libft, I cant't remember
			return (dirent->d_name);
		dirent = readdir(env_paths[0]);				// it will return . and .. as the first entries each time, will this be a problem ?
	}
	return (NULL);
}





// we will perhaps have to "prune" executable before this function
