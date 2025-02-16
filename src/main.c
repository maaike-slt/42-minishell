/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:52 by msloot            #+#    #+#             */
/*   Updated: 2025/02/16 19:28:55 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: $?
// TODO: validate that no readline multi line are possible
// TODO: have execve work with relative path

#ifndef TEST

/*
	rl_free_keymap(rl_get_keymap_by_name("emacs"));
	rl_free_keymap(rl_get_keymap_by_name("emacs-standard"));
	rl_free_keymap(rl_get_keymap_by_name("emacs-meta"));
	rl_free_keymap(rl_get_keymap_by_name("emacs-ctlx"));
	rl_free_keymap(rl_get_keymap_by_name("vi"));
	rl_free_keymap(rl_get_keymap_by_name("vi-move"));
	rl_free_keymap(rl_get_keymap_by_name("vi-command"));
	rl_free_keymap(rl_get_keymap_by_name("vi-insert"));
*/

static void	rl_clean(void)
{
	rl_clear_history();
	rl_clear_signals();
	rl_cleanup_after_signal();
	rl_free_line_state();
	rl_callback_sigcleanup();
	rl_callback_handler_remove();
	rl_free_undo_list();
}

int	main(int argc, char **argv, char **envp)
{
	char		**envp_cpy;
	t_status	status;

	status = 0;
	envp_cpy = envdup(envp);
	if (!envp_cpy)
		return (1);
	(void)argc;
	(void)argv;
	set_sigquit();
	set_sigint();
	loop(&status, &envp_cpy);
	ft_2d_free((void ***)&envp_cpy, ft_2d_size((const void **)envp_cpy));
	rl_clean();
	// FIXME: return (status) doesn't seem to work
	return (status);
}

#endif
