/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:53:42 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/16 16:54:07 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

volatile sig_atomic_t	g_msh_sig = 0;

void	handler_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, handler_sigint);
}

void	init_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_sigint);
}
