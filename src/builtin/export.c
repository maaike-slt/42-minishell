/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:34:24 by msloot            #+#    #+#             */
/*   Updated: 2025/02/18 23:18:13 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_invalid_identifier_error(char *arg)
{
	char	*msg;

	msg = ft_strjoin("`", arg);
	msg = ft_strjoin_free(msg, "': not a valid identifier", true, false);
	error("export", msg);
	free(msg);
	return (EX_ERR);
}

int	export(int argc, char **argv, char ***envp)
{
	size_t	i;
	int		ret;

	dbg_builtin(argc, argv);
	if (argc < 2)
		return (EX_OK);
	ret = EX_OK;
	i = 1;
	while (argv[i])
	{
		if (!argv[i][0])
			ret = print_invalid_identifier_error(argv[i]);
		else if (ft_is_in(argv[i], '='))
		{
			if (ft_strncmp(argv[i], "_=", 2) == 0)
				;
			else if (argv[i][0] == '=')
				ret = print_invalid_identifier_error(argv[i]);
			else
				ft_setenv_raw(envp, ft_strdup(argv[i]));
		}
		i++;
	}
	return (ret);
}
