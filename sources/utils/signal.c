/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:53:42 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/27 17:25:26 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_msh_sig = 0;

void	child_handler_sigquit(int signum)
{
	(void)signum;
	rl_on_new_line();
	rl_replace_line("abc", 0);
	rl_redisplay();
}

void	handler_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_msh_sig = 0;
	signal(SIGINT, handler_sigint);
}

void	child_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
}

void	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_sigint);
}

// CTRL + C fait un exit code de 130
