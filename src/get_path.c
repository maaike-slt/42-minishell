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

/// when relative path, need to append exec name to dir if exec ///
/// found in a dir.											    ///

char	*append_exec_to_path(char *exec_dir, char *executable)
{
	char	*appended;
	int		size_dir;
	int		size_exec;

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

/// cut the dir part of the string (../../.),from the exec name ///

char	**cut_exec_string(char *executable)
{
	char	**result;
	int		temp;
	int		i;

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
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	if (!separate(&result, executable, temp))
		return (NULL);
	return (result);
}

char	*search_abs_path(char *executable)
{
	DIR				*directory;
	struct dirent	*dirent;
	char			**cut;

	cut = cut_exec_string(executable);
	if (!cut)
		return (NULL);
	directory = opendir(cut[0]);
	if (!directory)
	{
		free_cut_n_close_dir(cut, directory);
		return (NULL);
	}
	dirent = readdir(directory);
	while (dirent)
	{
		if (!ft_strcmp(cut[1], dirent->d_name))
		{
			free_cut_n_close_dir(cut, directory);
			return (executable);
		}
		dirent = readdir(directory);
	}
	free_cut_n_close_dir(cut, directory);
	return (NULL);
}

char	*search_relative_path(char **env_pths, char *executable)
{
	DIR				*directory;
	struct dirent	*dirent;
	int				i;

	i = 0;
	while (env_pths[i])
	{
		directory = opendir(env_pths[i]);
		if (directory == NULL)
		{
			i++;
			continue ;
		}
		dirent = readdir(directory);
		while (dirent)
		{
			if (compare_exec_to_entry(executable, dirent->d_name, directory))
				return (env_pths[i]);
			dirent = readdir(directory);
		}
		closedir(directory);
		i++;
	}
	return (NULL);
}

/// two posibilities: relative path (use PATH), or absolute (cut the ///
/// dir and then search trough it)									 ///

char	*search_for_dir(char	**env_pths, char	*executable)
{
	char	*exec_dir;
	char	*append;

	if (ft_strchr(executable, '/'))
	{
		exec_dir = search_abs_path(executable);
		if (exec_dir == NULL)
			return (NULL);
		printf("%s\n", exec_dir);			//for testing
		return (exec_dir);
	}
	else
	{
		exec_dir = search_relative_path(env_pths, executable);
		if (exec_dir == NULL)
			return (NULL);
		append = append_exec_to_path(exec_dir, executable);
		printf("%s\n", append);				// for testing
		if (!append)
			return (NULL);
		return (append);
	}
	return (exec_dir);
}
