/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:37 by msloot            #+#    #+#             */
/*   Updated: 2024/12/01 17:54:36 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# define EX_ERR	1

# include "../libft/inc/libft.h"

# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sysexits.h>

# define PROMPT	"\033[1;32m>\033[0m "

typedef struct s_expression
{
	int		argc;
	char	**argv;
}	t_expression;

bool			loop(void);
char			*prompt(void);
t_expression	*parse(char *line);

#endif
