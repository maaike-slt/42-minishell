/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:59:21 by adelille          #+#    #+#             */
/*   Updated: 2024/12/01 22:27:57 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_arr_new(t_arr *arr, size_t cell_size)
{
	arr->p = malloc(cell_size * ARR_INIT_SIZE);
	if (!arr->p)
		return (false);
	arr->len = 0;
	arr->capacity = ARR_INIT_SIZE;
	arr->cell_size = cell_size;
	return (true);
}

size_t	ft_arr_add(t_arr *arr, void *cell)
{
	void	*new;

	if (arr->len == arr->capacity)
	{
		new = malloc(arr->cell_size * arr->capacity * 2);
		if (!new)
			return (0);
		ft_memcpy(new, arr->p, arr->cell_size * arr->capacity);
		free(arr->p);
		arr->p = new;
		arr->capacity *= 2;
	}
	ft_memcpy(arr->p + (arr->len * arr->cell_size), cell, arr->cell_size);
	arr->len++;
	return (arr->len);
}
