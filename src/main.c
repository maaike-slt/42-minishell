/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 22:18:52 by msloot            #+#    #+#             */
/*   Updated: 2025/02/28 18:39:32 by adelille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*
	rl_clear_signals();
	rl_cleanup_after_signal();
	rl_free_line_state();
	rl_callback_sigcleanup();
	rl_callback_handler_remove();
	rl_free_undo_list();
*/

static void	rl_clean(void)
{
	rl_clear_history();
}

static bool	shlvl(char ***envp)
{
	char	*shlvl;
	char	*new_shlvl;
	ssize_t	n;

	shlvl = ft_getenv(*envp, "SHLVL");
	if (!shlvl)
		n = 0;
	else
	{
		n = ft_aton(shlvl);
		if (n < 0)
			n = 0;
	}
	new_shlvl = ft_ntoa(n + 1);
	if (!new_shlvl)
		return (error("malloc", strerror(errno)), false);
	ft_setenv(envp, "SHLVL", new_shlvl);
	free(new_shlvl);
	if (!*envp)
		return (error("malloc", strerror(errno)), false);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	char		**envp_cpy;
	t_status	status;

	(void)argc;
	(void)argv;
	status = 0;
	envp_cpy = envdup(envp);
	if (!envp_cpy)
		return (EX_OSERR);
	if (!shlvl(&envp_cpy))
	{
		ft_2d_free((void ***)&envp_cpy, ft_2d_size((const void **)envp_cpy));
		return (EX_OSERR);
	}
	set_sigquit(SIG_IGN);
	set_sigint(&prompt_handler);
	loop(&status, &envp_cpy);
	ft_2d_free((void ***)&envp_cpy, ft_2d_size((const void **)envp_cpy));
	rl_clean();
	return (status);
}

#endif
