/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:54:18 by adelille          #+#    #+#             */
/*   Updated: 2025/02/09 18:20:57 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/* sep:
<
redirect input
cat < file.txt

>
redirect output
ls > file.txt

<<
heredoc
cat << EOF
Hello World
EOF

>>
append output
ls >> file.txt

|
pipe
ls | grep .c

;
sep
ls ; echo "Hello World"

&&
and
ls && echo "Hello World"

||
or
ls || echo "Hello World"
*/

/* modifiers:
\
escape
echo "Hello \"World\""

$
variable
echo $HOME

'
literal
echo 'Hello World'

"
literal with variable
echo "Hello $HOME"

*
wildcard
ls *.c
*/

size_t		exp_len(const char *line);

bool		is_exp_sep(char c);

bool		extract_args(t_exp *exp, char *line, size_t len, char **envp);
bool		extract_string(
				char **ret, const char *line, size_t *i, char **envp);
bool		extract_redirection(char **ret, const char *line, size_t *i);
char		*extract_single_quote(const char *line, size_t *i);
char		*extract_double_quote(const char *line, size_t *i, char **envp);
char		*extract_variable(const char *line, size_t *i, char **envp);

#endif
