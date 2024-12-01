/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:15:14 by adelille          #+#    #+#             */
/*   Updated: 2024/12/01 18:59:24 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_expression_list	*parse(char *line)
{
	t_expression_list	*head;
	/* size_t	i; */

	if (!line || line[0] == '\0')
		return (NULL)
	return (NULL);
}
