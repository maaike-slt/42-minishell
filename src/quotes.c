/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:28:34 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/17 15:28:37 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//bool	isquote(char *s)
//{
//	int	i;
//
//	i = 0;
//	while (s[i])
//	{
//		if (s[i] == '\'' || s[i] == '\"')
//			return (true);
//		i++;
//	}
//	return (false);
//}

int	count_q_expand(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

bool	put_in_counter(t_values *v, char *s, int *i, int *tab)
{
	char *var;
	int	index;
	char *expand;
	int		size_name_var;
	
	var = get_var(&s[1], &size_name_var);
	if (!var)
		return (false);
	if (check_var_exist(v, var, &index) == false)
	{
		(*i)++;
		return (true);				// je return true pour que le loop dans la func davant continue, false only for malloc fail
	}
	expand = get_expand(v->env[index]);
	if (!expand)
		return (false);
	*tab += count_q_expand(expand);
	free (expand);
	return (true);
}

bool	allocate_tab(t_values *v, int **tab)
{
	int	i;
	int	tab_counter;

	i = 0;
	tab_counter = 1;
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')
		{
			quote_redpip(&v->cmd_str_b[i], &i);
			tab_counter++;
			continue ;
		}
		i++;
	}
	*tab = malloc(sizeof(int) * (tab_counter + 1));
	if (!(*tab))
		return (false);
	ft_bzero(*tab, sizeof(int) * tab_counter);
	(*tab)[tab_counter] = -1;
	return (true);
}

bool	get_counter(t_values *v, int **tab)
{
	int	i;
	int	ind_tab;

	i = 0;
	ind_tab = 0;
	if (allocate_tab(v, tab) == false)
		return (false);
	while (v->cmd_str_b[i])
	{
		if (v->cmd_str_b[i] == '\'' || v->cmd_str_b[i] == '\"')
		{
			quote_redpip(&v->cmd_str_b[i], &i);
			ind_tab++;
			continue ;
		}
		if (v->cmd_str_b[i] == '$')			//je dois juste regarder si ya des quotes dans les env var et leurs nombres
		{
			if (put_in_counter(v, &v->cmd_str_b[i], &i, &(*tab)[ind_tab]) == false)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	do_quotes(t_values *values)
{
	int	*tab;

	tab = NULL;
	if (values->isquote == 0)
		return (true);
	if (get_counter(values, &tab) == false)
		return (false);
	free(tab);
	values->isquote = 0;
	return (true);
}

