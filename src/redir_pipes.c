/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:18:00 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/14 12:18:16 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redpip(char	c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	quote_redpip(char *s, int	*index)
{
	char	type;
	int		i;

	i = 1;
	type = s[0];
	while (s[i])
	{
		if (s[i] == type)
		{
			*index += i + 1;
			return ;
		}
		i++;
	}
	return ;
}

int	is_redpip_valid(t_values *v, char *s, int *step)
{
	int	i;

	i = 0;
	if (s[0] == '|' && !is_redpip(s[1]))		//if there is nothing after pipe, I will let the exec handle the error
	{
		v->redpip_counter++;
		*step = 1;
		return (1);
	}
	if ((s[0] == '<' || s[0] == '>') && !is_redpip(s[1]))
	{
		v->redpip_counter++;
		*step = 1;
		return (1);
	}
	if ((s[0] == '<' || s[0] == '>') && s[0] == s[1])		//normalement ici j'ai pas besoin de proteger sur la fin de la string parce que si s[1] c'est la fin je fais pas d'accès au dela
	{
		if (is_redpip(s[2]))
			return (-1);
		*step = 2;
		v->redpip_counter++;
		return (1);
	}
	return (-1);		// I think i need to put -1 here because of <| case
}

bool	redpip_token_counter(t_values *v)
{
	int	i;
	int	step;

	i = 0;
	while(v->cmd_str[i])		// FORGOT TO PARSE FOR QUOTES
	{
		step = 0;
		if (v->cmd_str[i] == '\'' || v->cmd_str[i] == '\"')
		{
			quote_redpip(&v->cmd_str[i], &i);
			continue;	
		}	
		if (is_redpip(v->cmd_str[i]))
		{
			if (is_redpip_valid(v, &v->cmd_str[i], &step) != -1)
			{
				i += step;
				continue;
			}
			v->redpip_counter = 0;
			return (false);
		}
		i++;
	}
	return (true);
}							// DONT FORGET TO REINITIALIZE REDPIP COUNTER AFTER EXEC IS DONE
