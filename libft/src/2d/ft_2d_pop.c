/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2d_pop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:45:59 by msloot            #+#    #+#             */
/*   Updated: 2024/12/05 19:49:59 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_2d_pop(void **ptr, size_t index)
{
	void	*ret;
	size_t	i;

	if (ptr == NULL || ptr[0] == NULL)
		return (NULL);
	ret = ptr[index];
	i = index;
	while (ptr[i])
	{
		ptr[i] = ptr[i + 1];
		i++;
	}
	return (ret);
}
