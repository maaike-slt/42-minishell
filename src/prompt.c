/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:19:10 by adelille          #+#    #+#             */
/*   Updated: 2024/12/15 18:04:02 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cwd(void)
{
	size_t	i;
	char	*cwd;
	char	*ret;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup(""));
	i = ft_strlen(cwd);
	while (i > 0 && cwd[i] != '/')
		i--;
	ret = ft_strdup(&cwd[i + 1]);
	free(cwd);
	return (ret);
}

/**
 * @brief Prompt the user for a bash input
 *
 * @return char* the user input (on the heap) or NULL if nothing
 */
char	*prompt(void)
{
	char	*prompt;
	char	*line;

	prompt = ft_strjoin_free(Y_B_MAG, get_cwd(), false, true);
	ft_strpush(&prompt, ' ');
	prompt = ft_strjoin_free(prompt, PROMPT, true, false);
	line = readline(prompt);
	free(prompt);
	// FIXME: continue to prompt if line is still escaping
	if (!line || line[0] == '\0')
		return (free(line), NULL);
	add_history(line);
	return (line);
}
