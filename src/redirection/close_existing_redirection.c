/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_existing_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adelille <adelille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:39:58 by adelille          #+#    #+#             */
/*   Updated: 2025/02/26 18:40:08 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	close_existing_redirection(t_exp *exp, char ir)
{
	if ((ir == IR_FILE_OUT || ir == IR_FILE_OUT_APPEND)
		&& exp->outfd > STDERR_FILENO)
	{
		if (close(exp->outfd) == -1)
			return (error("close", strerror(errno)), false);
	}
	else if ((ir == IR_FILE_IN || ir == IR_HEREDOC)
		&& exp->infd > STDERR_FILENO)
	{
		if (close(exp->infd) == -1)
			return (error("close", strerror(errno)), false);
	}
	return (true);
}
