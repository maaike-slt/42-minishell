/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_in_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:11 by adelille          #+#    #+#             */
/*   Updated: 2025/02/23 22:20:57 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

// must segfault if not found to alert for a bug
static size_t	get_key_len(const char *arg)
{
	size_t	i;

	i = 0;
	while (arg[i] != INTERNAL_VAR_END)
		i++;
	return (i);
}

static char	*get_var(const char *key, t_status *status, char **envp)
{
	char	*ret;

	if (ft_strcmp(key, "?") == 0)
	{
		ret = ft_itoa(*status);
		if (!ret)
			return (error("malloc", strerror(errno)), NULL);
		return (ret);
	}
	ret = ft_getenv(envp, key);
	if (!ret)
		return (NULL);
	ret = ft_strdup(ret);
	if (!ret)
		return (error("malloc", strerror(errno)), NULL);
	return (ret);
}

static bool	expand_var(char **arg, size_t i, t_status *status, char **envp)
{
	char	*key;
	size_t	key_len;
	char	*tmp;

	key_len = get_key_len(&(*arg)[i + 1]);
	key = ft_strndup(&(*arg)[i + 1], key_len);
	if (!key)
		return (error("malloc", strerror(errno)), false);
	tmp = get_var(key, status, envp);
	free(key);
	if (!tmp)
		return (ft_strcpy(&(*arg)[i], &(*arg)[i + key_len + 2]), true);
	tmp = ft_strjoin_free(tmp, &(*arg)[i + key_len + 2], true, false);
	if (!tmp)
		return (error("malloc", strerror(errno)), false);
	(*arg)[i] = '\0';
	*arg = ft_strjoin_free(*arg, tmp, true, true);
	if (!*arg)
		return (error("malloc", strerror(errno)), false);
	return (true);
}

bool	fill_in_var(t_exp *exp, t_status *status, char **envp)
{
	size_t	arg_i;
	size_t	char_i;

	arg_i = 0;
	while (arg_i < (size_t)exp->argc)
	{
		char_i = 0;
		while (exp->argv[arg_i][char_i])
		{
			if (exp->argv[arg_i][char_i] == INTERNAL_VAR_START)
			{
				if (!expand_var(&(exp->argv[arg_i]), char_i, status, envp))
					return (false);
			}
			else
				char_i++;
		}
		arg_i++;
	}
	return (true);
}
