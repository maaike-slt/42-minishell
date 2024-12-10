/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:37 by msloot            #+#    #+#             */
/*   Updated: 2024/12/10 23:17:33 by msloot           ###   ########.fr       */
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
}	t_exp;

void				exp_free(void *exp);

typedef struct s_expression_list
{
	t_exp						*content;
	struct s_expression_list	*next;
}	t_exp_list;

bool				loop(char **envp);
char				*prompt(void);
t_exp_list			*parse(char *line, char **envp);
void				init_signals(void);

typedef enum e_dispatch_code
{
	D_ERROR,
	D_EXIT,
	D_OKAY
}				t_dispatch;

void				init_signals(void);
bool				loop(char **envp);
char				*prompt(void);

t_dispatch			dispatch(const t_exp *exp, char **envp);

int					builtin(int argc, char **argv, char **envp);
int					cd(int argc, char **argv, char **envp);
int					echo(int argc, char **argv);
int					env(char **envp);
int					unset(int argc, char **argv, char **envp);
int					pwd(void);

ssize_t				find_env(char **envp, const char *key);
char				*ft_getenv(char **envp, const char *key);
char				**envdup(char **src);
char				**ft_setenv(char **envp, char *key, char *val);
char				**ft_setenv_raw(char **envp, const char *str);

void				error(const char *err_src, const char *msg);

void				dbg(const char *str);
void				dbg_builtin(int argc, char **argv);

# ifdef TEST

bool				assert(const char *name, bool r);
bool				assert_eq(const char *name, ssize_t got, ssize_t expected);
bool				assert_str_eq(const char *name,
						const char *got, const char *expected);

bool				test_exp_len(void);
bool				test_extract_args(void);

# endif

#endif
