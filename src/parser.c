/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:31:54 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/23 21:15:13 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	check_two_quotes(char *s, char type)
//{
//	int	size;
//
//	size = ft_strlen(s);
//	if (size == 1)
//		return (0);
//	if (s[0] == type && s[size - 1] == type)
//		return (1);
//	return (0);
//}
//
//int	manage_quote(char **word, char type)
//{
//	char *temp;
//	int	size;
//
//	if (!check_two_quotes(*word, type))
//	{
//		
//		return (0);
//	}
//	temp = *word;
//	size = ft_strlen(*word);
//	*word = malloc(sizeof(char) * (size - 1));
//	if (!(*word))
//	{
//		*word = temp;		//otherwise this would be a nightmare to free on exit (the big free in handle_cmd_str would double free I think) // maybe after refactor i can change this
//		return (-1);
//	}
//	ft_memcpy(*word, &temp[1], sizeof(char) * (size - 2));
//	(*word)[size - 2] = 0;
//	free(temp);
//	return(0);
//}

bool	other_quote(t_values *v, char *s, char type)
{
	int	i;

	i = 1;				// one here because otherwise it is on the quote if it found it
	while (s[i])
	{
		if(s[i] == type)
		{	
			if (check_quote(v, &s[++i]) == true)
			{
				v->isquote = 1;
				return (true);
			}
			return (false);
		}
		i++;
	}
	return (false);
}

bool	check_quote(t_values *v, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (other_quote(v, &s[i], s[i]) == true)
				return (true);
			return (false);			// careful this false return is only for testing
		}
		i++;
	}
	return (true);
}

bool	parser(t_values *values)
{
	char	**split_str;

	if (check_quote(values, values->cmd_str) == false)	// this function check if quotes are valid or not in the whole cmd_str
		return (false);
	if (redpip_token_counter(values) == false)
		return (false);
	if (expand(values) == false)
		return (false);
	split_str = ft_split_whitespace(values->cmd_str);
	if (!split_str || !split_str[0])		// !split[0] otherwise segfault if cmd_str is only spaces
	{
		free(values->cmd_str);
		if (split_str)
			free(split_str);
		return (false);
	}
	values->split_str= split_str;
	if (do_quotes(values) == false)
		return (false);
//	if (tokenise_redpip(values) == false)
//		return (false);
	return (true);
}
