/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:14:59 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 18:39:49 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

inline static bool	is_file_redirection(char c)
{
	return (c == '<' || c == '>');
}

static char	*extract_single_arg(
	const char *line, size_t *i, size_t len, t_env *e)
{
	char	*ret;

	ret = ft_strdup("");
	while (ret && *i < len && line[*i] && !ft_isspace(line[*i]))
	{
		if (is_file_redirection(line[*i]) && ret[0] != '\0')
			break ;
		if (extract_string(&ret, line, i, e))
			;
		else if (extract_redirection(&ret, line, i))
			return (ret);
		else
			ft_strpush(&ret, line[*i]);
		(*i)++;
	}
	return (ret);
}

bool	extract_args(t_exp *exp, char *line, size_t len, t_env *e)
{
	char	*arg;
	size_t	i;

	exp->argv = (char **)malloc(sizeof(char *));
	if (!exp->argv)
		return (false);
	exp->argv[0] = NULL;
	exp->argc = 0;
	i = 0;
	while (i < len)
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (i >= len)
			break ;
		arg = extract_single_arg(line, &i, len, e);
		if (!arg || !ft_2d_push((void ***)(&exp->argv), arg))
			return (ft_2d_free((void ***)(&exp->argv),
				ft_2d_size((const void **)exp->argv)), false);
		exp->argc++;
	}
	return (true);
}

#ifdef TEST

bool	test_extract_args(void)
{
	t_exp		exp;
	char		line[99];
	t_status	status;
	char		**envp;
	bool		r;

	envp = (char *[]){"HOME=/home/adelille", "USER=adelille", NULL};
	ft_strcpy(line, "yo \"ye; no\" 'oh | e'");
	r = EX_OK;
	r |= assert("extract_args yo \"ye; no\" 'oh | e'",
			extract_args(&exp, line, ft_strlen(line), &(t_env){&status, envp}));
	r |= assert_eq("exp.argc", exp.argc, 3);
	r |= assert("exp.argv != NULL", exp.argv != NULL);
	r |= assert_eq("exp.argv[0]", ft_strcmp(exp.argv[0], "yo"), 0);
	r |= assert_eq("exp.argv[1]", ft_strcmp(exp.argv[1], "ye; no"), 0);
	r |= assert_eq("exp.argv[2]", ft_strcmp(exp.argv[2], "oh | e"), 0);
	r |= assert("exp.argv[3] == NULL", exp.argv[3] == NULL);
	ft_2d_free((void ***)(&exp.argv), ft_2d_size((const void **)exp.argv));
	return (r);
}

#endif
