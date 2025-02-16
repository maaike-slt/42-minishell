/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:19:10 by adelille          #+#    #+#             */
/*   Updated: 2025/02/16 15:50:03 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cwd(char **envp)
{
	size_t	i;
	char	*cwd;
	char	*ret;
	char	*home;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup(""));
	if (ft_strcmp(cwd, "/") == 0)
		return (free(cwd), ft_strdup("/"));
	home = ft_getenv(envp, "HOME");
	if (home && ft_strcmp(cwd, home) == 0)
		return (free(cwd), ft_strdup("~"));
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
char	*prompt(char **envp, bool *exit)
{
	char	*prompt;
	char	*line;

	prompt = ft_strjoin_free(Y_B_MAG, get_cwd(envp), false, true);
	ft_strpush(&prompt, ' ');
	prompt = ft_strjoin_free(prompt, PROMPT, true, false);
	line = readline(prompt);
	free(prompt);
	if (!line)
	{
		*exit = true;
		rl_replace_line("exit", false);
		rl_redisplay();
		ft_putstr_fd("\n", STDERR_FILENO);
		return (NULL);
	}
	if (line[0] == '\0')
		return (free(line), NULL);
	add_history(line);
	return (line);
}
