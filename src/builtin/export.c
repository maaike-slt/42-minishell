/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 19:34:24 by msloot            #+#    #+#             */
/*   Updated: 2025/02/26 18:22:10 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*next_ordered_env(char **envp, size_t size, const char *current)
{
	char	*next;
	size_t	i;

	next = NULL;
	i = 0;
	while (i < size)
	{
		if ((!current || ft_strncmp(envp[i], current, ft_strlen(current)) > 0)
			&& (!next || ft_strncmp(envp[i], next, ft_strlen(next)) < 0))
			next = envp[i];
		i++;
	}
	return (next);
}

static void	print_sorted_env(char **envp)
{
	char	*current;
	size_t	size;
	size_t	i;

	size = ft_2d_size((const void **)envp);
	current = NULL;
	i = 0;
	while (i < size)
	{
		current = next_ordered_env(envp, size, current);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(current, STDOUT_FILENO);
		i++;
	}
}

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
		return (print_sorted_env(*envp), EX_OK);
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
