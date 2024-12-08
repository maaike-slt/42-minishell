/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 22:14:59 by adelille          #+#    #+#             */
/*   Updated: 2024/12/08 19:24:13 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

static char	*extract_single_arg(
	const char *line, size_t *i, size_t len, char **envp)
{
	char	*ret;

	ret = ft_strdup("");
	while (ret && *i < len && line[*i] && !ft_isspace(line[*i]))
	{
		if (line[*i] == '\'')
			ret = ft_strjoin_free(ret,
					extract_single_quote(line, i), true, true);
		else if (line[*i] == '"')
			ret = ft_strjoin_free(ret,
					extract_double_quote(line, i, envp), true, true);
		else if (line[*i] == '\\')
	    {
			(*i)++;
			ft_strpush(&ret, line[*i]);
	    }
		/*
		else if (line[*i] == '$')
			ret = ft_strjoin_free(ret, extract_variable(line, i, envp), true, true);
		*/
		else
			ft_strpush(&ret, line[*i]);
		(*i)++;
	}
	return (ret);
}

bool	extract_args(t_expression *exp, char *line, size_t len, char **envp)
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
		ft_putstr("i: ");
		ft_putnbr(i);
		ft_putchar('\n');
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (i >= len)
			break ;
		arg = extract_single_arg(line, &i, len, envp);
		ft_putstr("arg: ");
		ft_putstr(arg);
		ft_putchar('\n');
		if (!arg || !ft_2d_push((void ***)(&exp->argv), arg))
			return (ft_2d_free((void ***)(&exp->argv),
				ft_2d_size((const void **)exp->argv)), false);
		ft_putstr("exp->argv[exp->argc]: ");
		ft_putstr(exp->argv[exp->argc]);
		ft_putchar('\n');
		exp->argc++;
	}
	ft_putstr("exp->argc: ");
	ft_putnbr(exp->argc);
	ft_putchar('\n');
	return (true);
}

#ifdef TEST

bool	test_extract_args(void)
{
	t_expression	exp;
	char			line[99];
	char			**envp;
	bool			r;

	envp = (char *[]){"HOME=/home/adelille", "USER=adelille", NULL};
	ft_strcpy(line, "yo \"ye; no\" 'oh | e'");
	r = EX_OK;
	r |= assert("extract_args yo \"ye; no\" 'oh | e'",
			extract_args(&exp, line, ft_strlen(line), envp));
	/*
	ft_putstr("exp.argv[0]: ");
	ft_putstr(exp.argv[0]);
	ft_putchar('\n');
	r |= assert_eq("exp.argc", exp.argc, 3);
	r |= assert("exp.argv != NULL", exp.argv != NULL);
	ft_putstr("exp.argv[0]: ");
	ft_putstr(exp.argv[0]);
	ft_putchar('\n');
	r |= assert_eq("exp.argv[0]", ft_strcmp(exp.argv[0], "yo"), 0);
	r |= assert_eq("exp.argv[1]", ft_strcmp(exp.argv[1], "ye; no"), 0);
	r |= assert_eq("exp.argv[2]", ft_strcmp(exp.argv[2], "oh | e"), 0);
	*/
	r |= assert("exp.argv[3] == NULL", exp.argv[3] == NULL);
	ft_2d_free((void ***)(&exp.argv), ft_2d_size((const void **)exp.argv));
	return (r);
}

#endif
