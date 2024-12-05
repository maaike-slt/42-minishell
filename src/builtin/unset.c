/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 21:03:51 by msloot            #+#    #+#             */
/*   Updated: 2024/12/05 22:10:23 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: add 2d functions to libft
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

void	ft_2d_drop(void **ptr, size_t index)
{
	free(ft_2d_pop(ptr, index));
}

int	unset(t_args *arg)
{
	ssize_t	index;

	// TODO check for right number of args
	index = find_env((const char **)(arg->envp), arg->argv[1]);
	if (index != -1)
	{
		// handle not found
		return (0);	// must be the same return as in `bash`
	}
	
}
