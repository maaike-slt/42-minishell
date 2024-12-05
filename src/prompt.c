/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:19:10 by adelille          #+#    #+#             */
/*   Updated: 2024/12/05 22:04:40 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prompt the user for a bash input
 *
 * @return char* the user input (on the heap) or NULL if nothing
 */
char	*prompt(void)
{
	char	*line;

	line = readline(PROMPT);
	// FIXME: continue to prompt if line is still escaping
	if (!line || line[0] == '\0')
		return (free(line), NULL);
	add_history(line);
	return (line);
}
