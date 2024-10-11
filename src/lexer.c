/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:31:54 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/09 15:31:56 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_two_quotes(char *s, char type)
{
	int	size;

	size = ft_strlen(s);
	if (size == 1)
		return (0);
	if (s[0] == type && s[size - 1] == type)
		return (1);
	return (0);
}

int	manage_quote(char **word, char type)
{
	char *temp;
	int	size;

	if (!check_two_quotes(*word, type))
	{
		
		return (0);
	}
	temp = *word;
	size = ft_strlen(*word);
	*word = malloc(sizeof(char) * (size - 1));
	if (!(*word))
	{
		*word = temp;		//otherwise this would be a nightmare to free on exit (the big free in handle_cmd_str would double free I think) // maybe after refactor i can change this
		return (-1);
	}
	ft_memcpy(*word, &temp[1], sizeof(char) * (size - 2));
	(*word)[size - 2] = 0;
	free(temp);
	return(0);
}

bool	check_right_n_quotes(t_values *values)
{
}

bool	lexer(t_values *values)
{
	int	i;

	i = 0;
//	if (check_right_n_quotes(values))
//		return (false);
	while(values->split_str[i])
	{
		if (manage_quote(&values->split_str[i], '\''))
			return (false);
		if (manage_quote(&values->split_str[i], '\"'))
			return (false);
		i++;
	}
	return (true);
}
