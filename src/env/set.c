/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:13:30 by msloot            #+#    #+#             */
/*   Updated: 2024/12/10 23:17:07 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_setenv_raw(char **envp, const char *str)
{
	return ((char **)ft_2d_push((void ***)&envp, (void *)str));
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