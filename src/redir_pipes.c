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
	if (!c)
		return (-1);
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

int	is_pip(t_values *v, char *s, int *step)
{
	if (s[0] == '|')				// oui mais quand il y a que | et pas  de redir ou pip après ?
	{
		if (s[1] == '|')
		{
			if (is_redir(v, &s[2], step) == true)
			{
				if (s[2]== '|')
					return (-1);
				v->redpip_counter += 2;
				(*step) += 2;
				return (1);
			}
			return (-1);
		}
		if (!ft_strncmp(s, "|>|", 3))
		{
			if (is_redpip(s[3]) == 1)
				return (-1);
			v->redpip_counter += 3;
			(*step) += 3;
			return (1);
		}
		if (is_redir(v, &s[1], step) == true)
		{
			v->redpip_counter++;
			(*step)++;
			return (1);
		}
		return (-1);
	}
	return (0);
}

bool	is_redir(t_values *v, char *s, int *step)
{
	if (!(*s))
		return (true);
	if (s[0] == '<' || s[0] == '>')			// only need to check if !(*s) because of is_pip func, otherwise it cant do a wrong array access
	{
		if (s[0] == s[1])		// non meme ici cette logique fonctionne pas, car si il ya s[2] en redir tok il faut pas que ça fonctionne
		{
			if (s[1])		// need to check s[1] for NULL in order not to have wrong array access, if check s[2] and s[1] is NULL it is a wrong array access
			{
				if (is_redpip(s[2]) == 1)
					return (false);
			}
			v->redpip_counter += 2;
			(*step) += 2;
			return (true);
		}
		if (s[0] == '>' && s[1]== '|')
		{
			if (is_redpip(s[2]) == 1)
				return (false);
			(*step) += 2;
			v->redpip_counter += 2;
			return (true);
		}
		if (!is_redpip(s[1]) || is_redpip(s[1]) == -1)
		{
			(*step)++;
			v->redpip_counter++;
			return (true);
		}
		return (false);			// here it is when <> for example
	}
	return (true);				// ouai mais non parce que si yavait | et que ça passe dans cette func et que après ya | ça va retrun true
}

		
			
	
	

int	is_redpip_valid(t_values *v, char *s, int *step)
{
	int	status;

	status = is_pip(v, s, step);
	if (status == -1)
		return (-1);
	else if (status == 1)
		return (1);
	if (is_redir(v, s, step) == false)
		return (-1);
	return (1);				//ah ouai mais non en fait ici le 
}
//
//	int	i;
//
//	i = 0;
//	if (s[0] == '|' && !is_redpip(s[1]))		//if there is nothing after pipe, I will let the exec handle the error
//	{
//		v->redpip_counter++;
//		*step = 1;
//		return (1);
//	}
//	if ((s[0] == '<' || s[0] == '>') && !is_redpip(s[1]))		// ouai deja ici c'est pas bon parce que je rejette >|
//	{
//		v->redpip_counter++;
//		*step = 1;
//		return (1);
//	}
//	if ((s[0] == '<' || s[0] == '>') && s[0] == s[1])		//normaly dont need to protect for acces out of bounds because if s[0] is NULL program wont go in this function
//	{
//		if (is_redpip(s[2]))			// ouai la yavait un wrong access en fait// ouai je pense qu'il y a avait un wrong access ici, mais ce que je faisais c'est que a la moindre detec wrong tok je
//return le programme, pas bete.
//			return (-1);
//		*step = 2;
//		v->redpip_counter++;
//		return (1);
//	}
//	return (-1);		// I think i need to put -1 here because of <| case
//}

bool	redpip_token_counter(t_values *v)
{
	int	i;
	int	step;

	i = 0;
	while(v->cmd_str[i])
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
}
