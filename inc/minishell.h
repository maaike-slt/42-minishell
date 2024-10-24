/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:18:41 by msloot            #+#    #+#             */
/*   Updated: 2024/10/23 21:24:44 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_values
{
	int		isquote;
	char	**env;
	char	*cmd_str;
	char	*cmd_str_b;		// ASK: what does "b" stand for?		// not a good name, it means backup, for complicated reason I need to dup the readline string, I meant to change this name to something like original_cmd_str
	char	*abs_path_bin;
	char	**split_str;
	char	**tokenized_str;
	int		prev_ret_val;
	int		redpip_counter;
}t_values;

// parsing //
bool	handle_cmd_str(t_values *values);
bool	parser(t_values *values);

// expand //
bool	expand(t_values *v);
char	*get_var(char *s, int *size);
bool	put_in_string(char **s, char *var, int *pos, int s_n_var);
int		get_len_till_eq(char	*s);
int		do_retval(t_values *v, char *s, int *i);
bool	do_put_in_string(t_values *v, char *var, int *i, int size_name_var);
char	*get_expand(char *s);
bool	check_var_exist(t_values *v, char *var, int *index);

// redir and pipes //
bool	redpip_token_counter(t_values *values);
void	quote_redpip(char *s, int	*index);
bool	is_redir(t_values *v, char *s, int *step);
int		is_redpip(char	c);
int		pip_case_s(t_values *v, char *s, int *step);
bool	redir_case_equal(t_values *v, char*s, int *step);
bool	redir_case_r_n_s(t_values *v, char *s, int *step);

// quote parsing //
bool	check_quote(t_values *values, char *s);
bool	quote_parsing(t_values *values, int	*tab);

// quote resolving //
bool	do_quotes(t_values *values);
bool	manage_q_tok(t_values *v, int x, char type, int count);
void	 copy_in_tok(t_values *v, char *s, int x, char type, int count);
void	manage_rest_tok(t_values *v, int x, char *new_tok, char type);

//directory functions //
char	*search_for_dir(t_values *values, char	**env_paths, char *executable);
char	*check(t_values *values, char *path);

// get_path_utils //
bool	compare_exec_to_entry(char *executable, char *entry, DIR *directory);
void	free_cut_n_close_dir(char **cut, DIR *directory);
bool	separate(char ***result, char *executable, int temp);
char	*set_ret_val(t_values *values);
char	*is_dir(t_values *values, char *path);
void	handl_z(int x);

// path_splitting //
char	*get_abs_path(t_values *values);

// signals //
int	set_sig_handler(void);

// exec //
int	exec(t_values *values);

#endif
