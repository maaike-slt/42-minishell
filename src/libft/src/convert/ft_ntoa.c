/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ntoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:57:55 by msloot            #+#    #+#             */
/*   Updated: 2023/11/21 19:57:57 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ntoa(ssize_t n)
{
	return (ft_ntoa_base(n, &(t_base){B10, B10_LEN}));
}
