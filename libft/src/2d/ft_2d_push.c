/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 21:22:03 by msloot            #+#    #+#             */
/*   Updated: 2024/12/14 18:29:29 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_2d_push(void ***ptr, void *val)
{
	size_t	size;
	size_t	i;
	void	**new;

	size = ft_2d_size((const void **)*ptr);
	new = (void **)malloc(sizeof(void *) * (size + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = (*ptr)[i];
		i++;
	}
	new[i] = val;
	new[i + 1] = NULL;
	free(*ptr);
	*ptr = new;
	return (new);
}
