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
	char	*abs_path;
	char	**bin_args;
	int		prev_ret_val;
}t_values;

// parsing //
bool	parse(t_values *values);

//	directory functions //
char	*search_for_dir(t_values *values, char	**env_paths, char *executable);
char	*check(t_values *values, char *path);

//  get_path_utils //
bool	compare_exec_to_entry(char *executable, char *entry, DIR *directory);
void	free_cut_n_close_dir(char **cut, DIR *directory);
bool	separate(char ***result, char *executable, int temp);

// path_splitting //
char	*get_abs_path(t_values *values, char *executable);

// signals //
int	set_sig_handler(void);

// executing //
int	execute(t_values *values);

#endif
