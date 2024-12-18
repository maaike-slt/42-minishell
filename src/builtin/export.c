/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:34:24 by msloot            #+#    #+#             */
/*   Updated: 2024/12/14 19:34:37 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(int argc, char **argv, char ***envp)
{
	size_t	i;

	dbg_builtin(argc, argv);
	if (argc < 2)
		return (EX_OK);
	i = 1;
	while (argv[i])
	{
		if (ft_is_in(argv[i], '='))
			ft_setenv_raw(envp, argv[i]);
		i++;
	}
	return (EX_OK);
}
