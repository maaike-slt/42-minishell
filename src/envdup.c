/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:40:05 by msloot            #+#    #+#             */
/*   Updated: 2024/12/07 19:55:16 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envdup(char **src)
{
	size_t	i;
	size_t	size;
	char	**dst;

	size = ft_2d_size((const void **)src);
	dst = (char **)malloc(sizeof(char *) * size);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			return (ft_2d_free((void ***)&dst, ft_2d_size((const void **)dst)),
				NULL);
		i++;
	}
	return (dst);
}
