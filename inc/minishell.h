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

typedef struct s_signals
{
	struct sigaction	sig_c;
	struct sigaction	sig_slash;
}t_signals;

// parsing //
bool	parse(char *prompt);

//	directory functions //
char	*search_for_dir(char	**env_paths, char *executable);

//  get_path_utils //
bool	compare_exec_to_entry(char *executable, char *entry, DIR *directory);
void	free_cut_n_close_dir(char **cut, DIR *directory);
bool	separate(char ***result, char *executable, int temp);

// path_splitting //
char	*get_abs_path(char *executable);

// signals //
int	set_sig_handler(t_signals *signals);
int	event(void);

#endif
