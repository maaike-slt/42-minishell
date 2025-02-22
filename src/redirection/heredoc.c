/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:47:19 by adelille          #+#    #+#             */
/*   Updated: 2025/02/18 22:48:46 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	heredoc(t_exp *exp)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open(HEREDOC_TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (error("open", strerror(errno)), false);
	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			return (false);
		if (ft_strcmp(line, exp->argv[exp->argc - 1]) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	exp->infd = open(HEREDOC_TMP_FILE, O_RDONLY);
	return (true);
}
