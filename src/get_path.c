/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:03:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/25 19:52:46 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_exec_to_path(char *exec_dir, char *executable)
{
	char	*appended;
	int size_dir;
	int size_exec;

	size_dir = ft_strlen(exec_dir);
	size_exec = ft_strlen(executable);
	appended = malloc(sizeof(char) * (size_dir + size_exec + 2));
	if (!appended)
		return (NULL);
	ft_memcpy(appended, exec_dir, size_dir);
	ft_memcpy(&appended[size_dir + 1], executable, size_exec);
	appended[size_dir] = '/';
	appended[size_dir + size_exec + 1] = 0;
	return (appended);
}

char	**cut_exec_string(char *executable)
{
	char	**result;
	int	temp;
	int i;

	i = 0;
	temp = 0;
	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	while (executable[i])
	{
		if (executable[i] == '/')
			temp = i;
		i++;
	}
	if (!temp)		//don't need this if abs/rel parsing done right, this is a safeguard, remove once testing done if needed for norm.
	{
		free(result);
		return(NULL);
	}
	result[0] = ft_strndup(executable, temp + 2);
	if (!result[0])
		return (NULL);
	result[0][temp + 1] = 0;
	result[1] = ft_strdup(executable + (temp +1));
	if (!result[1])
	{
		free(result[0]);
		free(result);
		return (NULL);
	}
	return (result);
}

char	*search_abs_path(char *executable)
{
	DIR	*directory;
	struct dirent *dirent;
	char	**cut;

	cut = cut_exec_string(executable);
	if (!cut)
		return (NULL);
	directory = opendir(cut[0]);
	if (!directory)
	{
		return (NULL);
	}
	dirent = readdir(directory);
	while (dirent)
	{
		if (!ft_strcmp(cut[1], dirent->d_name))
		{
			free(cut[0]);
			free(cut[1]);
			free(cut);
			closedir(directory);	
			return (executable);
		}
		dirent = readdir(directory);
	}
	closedir(directory);
	free(cut[0]);
	free(cut[1]);
	free(cut);
	return (NULL);
}

char	*search_relative_path(char **env_pths, char *executable)
{
	DIR *directory;
	struct dirent *dirent;
	int	i;

	i = 0;
	while (env_pths[i])
	{
		directory =	opendir(env_pths[i]);
		if (directory == NULL)
		{
			i++;
			continue;
		}
		dirent = readdir(directory);	// careful, if we give . or .. as executable, it will return a dir		// also as there is a limit of 256 char in dirent->d_name, check what does an overflow of the array does
		while(dirent)
		{
			if (!ft_strcmp(executable, dirent->d_name))
			{
				closedir(directory);
				return (env_pths[i]);
			}
			dirent = readdir(directory);
		}
		closedir(directory);
		i++;
	}
	return (NULL);
}

char	*search_for_dir(char	**env_pths, char	*executable)
{
	char	*exec_dir;
	char	*append;

	if (ft_strchr(executable, '/'))
	{
		exec_dir = search_abs_path(executable);
		if (exec_dir == NULL)
			return (NULL);
		printf("%s\n", exec_dir);
		return (exec_dir);
	}
	else
	{
		exec_dir = search_relative_path(env_pths, executable);
		if (exec_dir == NULL)
			return (NULL);
		append = append_exec_to_path(exec_dir, executable);
		printf("%s\n", append);
		if (!append)
			return (NULL);
		return (append);
	}
	return	(exec_dir);
}
