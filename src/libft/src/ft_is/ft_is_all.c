/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:17:08 by msloot            #+#    #+#             */
/*   Updated: 2024/05/12 17:25:12 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// crash if f is NULL
bool	ft_is_all(const char *str, bool (*f)(char))
{
	size_t	i;

	if (!str)
		return (true);
	i = 0;
	while (str[i])
	{
		if (!f(str[i]))
			return (false);
		i++;
	}
	return (true);
}
