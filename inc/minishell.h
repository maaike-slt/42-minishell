/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:37 by msloot            #+#    #+#             */
/*   Updated: 2024/12/03 21:54:58 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# define EX_ERR	!EX_OK

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

typedef enum e_dispatch_code
{
	D_ERROR,
	D_EXIT,
	D_OKAY
}				t_dispatch;

typedef struct s_args
{
	size_t	argc;
	char	**argv;
	char	**envp;
}	t_args;

void		init_signals(void);
bool		loop(char **envp);
char		*prompt(void);

t_dispatch	dispatch(t_args *arg);

int			builtin(t_args *arg);
int			cd(t_args *arg);
int			echo(t_args *arg);
int			env(char **envp);
int			pwd(void);

ssize_t		find_env(const char **envp, const char *key);

void		error(const char *err_src, const char *msg);

#endif
