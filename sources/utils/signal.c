/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:53:42 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/04 14:39:01 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_msh_sig = 0;

void	handler_sigint(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_msh_sig = 0;
	signal(SIGINT, handler_sigint);
}

void	handler_sigint_exec(int signum)
{
	(void)signum;
	g_msh_sig = SIGINT;
	write(1, "\n", 1);
}

void	child_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
}

void	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_sigint);
}
