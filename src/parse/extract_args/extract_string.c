/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:57:22 by adelille          #+#    #+#             */
/*   Updated: 2025/02/18 23:33:00 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static char	*extract_tilde(char **envp)
{
	char	*home;

	home = ft_getenv(envp, "HOME");
	if (!home)
		return ("~");
	return (home);
}

bool	extract_string(char **ret, const char *line, size_t *i, t_env *e)
{
	if (line[*i] == '\'')
		*ret = ft_strjoin_free(*ret,
				extract_single_quote(line, i), true, true);
	else if (line[*i] == '"')
		*ret = ft_strjoin_free(*ret,
				extract_double_quote(line, i, e), true, true);
	else if (line[*i] == '\\')
	{
		(*i)++;
		ft_strpush(ret, line[*i]);
	}
	else if (line[*i] == '$')
		*ret = ft_strjoin_free(*ret,
				extract_variable(line, i, e), true, true);
	else if (!(*ret)[0] && line[*i] == '~' && is_variable_sep(line[*i + 1]))
		*ret = ft_strdup(extract_tilde(e->envp));
	else
		return (false);
	return (true);
}
