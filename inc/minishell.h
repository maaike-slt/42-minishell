/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:37 by msloot            #+#    #+#             */
/*   Updated: 2024/12/01 22:28:30 by adelille         ###   ########.fr       */
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

typedef struct s_arr
{
	void	*p;
	size_t	len;
	size_t	capacity;
	size_t	cell_size;
}   t_arr;

#define ARR_INIT_SIZE 32

bool	ft_arr_new(t_arr *arr, size_t cell_size);
size_t	ft_arr_add(t_arr *arr, void *cell);

typedef struct s_expression
{
	int		argc;
	char	**argv;
}	t_expression;

typedef struct s_expression_list
{
	t_expression				*expression;
	struct s_expression_list	*next;
}	t_expression_list;

bool				loop(void);
char				*prompt(void);
t_expression_list	*parse(char *line);

#endif
