/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:56:31 by gbonis            #+#    #+#             */
/*   Updated: 2024/10/14 16:56:33 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_retval(t_values *v, char *s, int *i)
{
	char *c_retval;

	if (s[1] == '?')
	{
		c_retval = ft_itoa(v->prev_ret_val);
		if (!c_retval)
			return (false);
		if (put_in_string(&v->cmd_str, c_retval, i, 1) == false)
		{
			free(c_retval);
			return (-1);
		}
		free(c_retval);
		return (1);
	}
	return (0);
}

int		get_len_till_eq(char	*s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '=')
		i++;
	return (i);	
}	

void	copy_end(char	*dest, char	*from)
{
	int	i;

	i = 0;
	while(from[i])
	{
		dest[i] = from[i];
		i++;
	}					// put \0 here is better
}

void	copy_until(char *dest, char *from, int pos)
{
	int	i;

	i = 0;
	while (pos)
	{
		dest[i] = from[i];
		pos--;
		i++;
	}
}

bool	put_in_string(char **s, char *var, int *pos, int s_n_var)
{
	char	*new;
	int		s_var;
	int		s_s;
	int		temp_pos;

	temp_pos = *pos;
	s_var = ft_strlen(var);	
	s_s = ft_strlen(*s);
	if ((*s)[temp_pos] != '$')
		return (false);
	new = malloc(sizeof(char) * (s_s - (s_n_var + 1) + s_var + 1));
	copy_until(new, *s, temp_pos);
	copy_until(&new[temp_pos], var, s_var);
	copy_end(&new[temp_pos + s_var], &(*s)[temp_pos + s_n_var + 1]);
	free(*s);
	*pos = temp_pos + s_var;
	new[s_s - (s_n_var + 1) + s_var] = 0;
	*s = new;
	return (true);
}
