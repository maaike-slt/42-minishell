/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:45:45 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/20 09:48:17 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	main()
{
	char	*prompt;
	char	*cmd_str;

	prompt = "minishell$ ";
	cmd_str = readline(prompt);
	parse(cmd_str);
	return (0);
}
