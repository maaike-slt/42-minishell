/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:12:53 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/14 15:12:54 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *s, int *size)			// faire l'index ici pour avoir le numéro d'après la variable, pour pouvoir faire les maths 
{
	char	*var;
	int		i;
	int		y;

	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	if (!i)
		return (NULL);
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	y = 0;
	while (i)
	{
		var[y] = s[y];
		i--;
		y++;
	}
	*size = i;
	var[y] = 0;
	return (var);
}

bool	check_var_exist(t_values *v, char *var, int *index)
{
	int	i;

	i = 0;
	while (v->env[i])
	{
		if (!ft_strncmp(var, v->env[i], ft_strlen(var)))
		{
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

char	*get_expand(char *s)
{
	char	**split;
	char	*temp;

	split = ft_split(s, '=');
	if (!split)
		return (NULL);
	temp = split[1];
	free(split[0]);
	free(split);
	return (temp);
}	

bool	do_expand(t_values *v, char *s, int *i)			// i need to have the index of the begin of the var before, to double check if i cut at the right place, but i need to be able to manipulate the i of expand loop
{
	char *var;
	char *expand;
	int	index;
	int	size_name_var;

	///// here I have enough space to do an if with retval/$?	
	var = get_var(&s[1], &size_name_var);		// dont forget to free		en fait faudrait que je chope d'abord l'index d'après la var içi avant de cutter, et de faire des maths pour savoir ou continuer une fois que j'ai cutté et remalloc la string
	if (!var)
		return (false);
	size_name_var = ft_strlen(var);
	if (check_var_exist(v, var, &index) == false)
	{
		free(var);
		return (false);
	}
	expand = get_expand(v->env[index]);
	if (put_in_string(&v->cmd_str, expand, i, size_name_var) == false)				// i is manipulated here
	{
		free(expand);
		free(var);
		return (false);
	}
	free(expand);
	free(var);
	return (true);
}

bool	expand(t_values *v)
{
	int		i;

	i = 0;
	while(v->cmd_str[i])
	{
		if (v->cmd_str[i] == '\'' || v->cmd_str[i] == '\"')
		{
			quote_redpip(&v->cmd_str[i], &i);
			continue;	
		}
		if (v->cmd_str[i] == '$')						// do somewhere here the tilde ?
		{
			if (do_expand(v, &v->cmd_str[i], &i) == false)			// je fais faire un truc avec manipulation du i via pointeur, je vais switcher la cmd_str et set le i au bon endroit depuis cette fonction
				return (false);
			continue;
		}
		i++;
	}
	return (true);
}
		
