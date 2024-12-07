/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 21:54:18 by adelille          #+#    #+#             */
/*   Updated: 2024/12/08 17:51:07 by adelille         ###   ########.fr       */
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
separator
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

bool		is_expression_separator(char c);
bool		is_arg_separator(char c, char quote);

bool		extract_args(t_expression *exp, char *line, size_t len, char **envp);
char		*extract_single_quote(const char *line, size_t *i);
char		*extract_double_quote(const char *line, size_t *i, char **envp);

#endif
