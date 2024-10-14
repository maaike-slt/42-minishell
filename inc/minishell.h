/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:18:41 by msloot            #+#    #+#             */
/*   Updated: 2024/10/05 18:44:39 by gbonis           ###   ########.fr       */
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
	char	**env;
	char	*cmd_str;
	char	*abs_path_bin;
	char	**split_str;
	char	**tokenized_str;
	int		prev_ret_val;
	int		redpip_counter;
}t_values;

// parsing //
bool	handle_cmd_str(t_values *values);
bool	parser(t_values *values);

//redir and pipes//
bool	redpip_token_counter(t_values *values);

// quote parsing //
bool	check_quote(char *s);

//	directory functions //
char	*search_for_dir(t_values *values, char	**env_paths, char *executable);
char	*check(t_values *values, char *path);

//  get_path_utils //
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
