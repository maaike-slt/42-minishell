/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:13:30 by msloot            #+#    #+#             */
/*   Updated: 2024/12/10 23:29:11 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_setenv_raw(char **envp, const char *str)
{
	ssize_t	index;

	index = find_env(envp, str);
	if (index == -1)
		return ((char **)ft_2d_push((void ***)&envp, (void *)str));
	free(envp[index]);
	envp[index] = (char *)str;
	return (envp);
}

char	**ft_setenv(char **envp, char *key, char *val)
{
	size_t	key_len;
	size_t	val_len;
	size_t	str_len;
	char	*str;

	key_len = ft_strlen(key);
	val_len = ft_strlen(val);
	str_len = key_len + val_len + 1;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	ft_strcpy(str, key);
	str[key_len] = '=';
	ft_strcpy(&str[key_len + 1], val);
	free(key);
	free(val);
	return (ft_setenv_raw(envp, str));
}
