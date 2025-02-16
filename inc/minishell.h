/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:37 by msloot            #+#    #+#             */
/*   Updated: 2025/02/16 17:33:44 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

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
# include <fcntl.h>

# define PROMPT	"\033[38;2;17;240;188m\033[0m  "
# define HEREDOC_PROMPT	"\033[2m↬\033[0m "

# define INTERNAL_PIPE_FD	-42

enum e_internal_redirection_type
{
	IR_FILE_IN = -1,
	IR_FILE_OUT = -2,
	IR_HEREDOC = -3,
	IR_FILE_OUT_APPEND = -4,
};

# define HEREDOC_TMP_FILE	"/tmp/minishell_heredoc"

typedef struct s_expression
{
	int		argc;
	char	**argv;
	int		infd;
	int		outfd;
}	t_exp;

void				exp_free(void *exp);

typedef struct s_expression_list
{
	t_exp						*content;
	struct s_expression_list	*next;
}	t_exp_list;

typedef int8_t			t_status;

enum e_exit_code
{
	EX_CHILD = -1,
	EX_ERR = 1,
	EX_NOTFOUND = 127
};

typedef enum e_dispatch_code
{
	D_ERROR,
	D_EXIT,
	D_OKAY
}	t_dispatch;

volatile sig_atomic_t	g_signum;
void				set_sigquit(void);
void				set_sigint(void);
void				ignore_sigint(void);

bool				loop(t_status *status, char ***envp);
char				*prompt(t_status *status, char **envp, bool *exit);
t_exp_list			*parse(char *line, char **envp);

bool				create_file_redirection(t_exp_list *exp_list);
bool				create_pipe(t_exp_list *exp_list);
bool				heredoc(t_exp *exp);

bool				exec_all_exp(t_exp_list *exp_list, char ***envp);
t_dispatch			dispatch(t_exp *exp, char ***envp);
bool				is_builtin(const char *cmd);
bool				prepare_bin(t_exp *exp, char **envp);
char				*find_bin_path(const char *cmd, char **envp);

typedef int (			*t_runner)(int argc, char **argv, char ***envp);
int					init_process(t_exp *exp, char ***envp, t_runner runner);
int					run_builtin(int argc, char **argv, char ***envp);
int					run_bin(int argc, char **argv, char ***envp);

# define BUILTIN_COUNT 6

int					builtin(int argc, char **argv, char ***envp);
int					cd(int argc, char **argv, char ***envp);
int					echo(int argc, char **argv);
int					env(char **envp);
int					unset(int argc, char **argv, char **envp);
int					export(int argc, char **argv, char ***envp);
int					pwd(void);

ssize_t				find_env(char **envp, const char *key);
char				*ft_getenv(char **envp, const char *key);
char				**envdup(char **src);
char				**ft_setenv(char ***envp, const char *key, const char *val);
char				**ft_setenv_raw(char ***envp, char *str);

void				error(const char *err_src, const char *msg);

# define DEBUG_PREFIX	"\033[1;36m[DEBUG]\033[0m\t"

void				dbg(const char *str);
void				dbg_number(const char *prefix, ssize_t nbr);
void				dbg_builtin(int argc, char **argv);

# ifdef TEST

bool				assert(const char *name, bool r);
bool				assert_eq(const char *name, ssize_t got, ssize_t expected);
bool				assert_str_eq(const char *name,
						const char *got, const char *expected);

char				**dummy_envp(char *first);

bool				test_exp_len(void);
bool				test_extract_args(void);
bool				test_extract_double_quote(void);
bool				test_extract_single_quote(void);
bool				test_extract_variable(void);

# endif

#endif
