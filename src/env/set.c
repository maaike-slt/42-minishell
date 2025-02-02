/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:13:30 by msloot            #+#    #+#             */
/*   Updated: 2024/12/15 19:30:37 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_setenv_raw(char ***envp, char *str)
{
	size_t	key_len;
	ssize_t	index;

	key_len = 0;
	while (str[key_len] != '=' && str[key_len])
		key_len++;
	str[key_len] = '\0';
	index = find_env(*envp, str);
	str[key_len] = '=';
	if (index == -1)
		return ((char **)ft_2d_push((void ***)envp, (void *)str));
	free((*envp)[index]);
	(*envp)[index] = str;
	return (*envp);
}

char	**ft_setenv(char ***envp, const char *key, const char *val)
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
	return (ft_setenv_raw(envp, str));
}
