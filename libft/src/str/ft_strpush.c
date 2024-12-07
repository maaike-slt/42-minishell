/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:56:50 by msloot            #+#    #+#             */
/*   Updated: 2024/12/07 20:01:02 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpush(char **str, char c)
{
	size_t	len;
	char	*new;

	if (!str || !*str)
		return (ft_strndup(&c, 1));
	len = ft_strlen(*str);
	new = (char *)malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	ft_strcpy(new, *str);
	new[len] = c;
	new[len + 1] = '\0';
	free(*str);
	*str = new;
	return (*str);
}
