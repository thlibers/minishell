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

void  handler_sigquit(int signum)
{
	(void)signum;
	rl_redisplay();
}


void  handler_sigint(int signum)
{
	(void)signum;
}

bool  init_signal(t_minishell *minishell)
{
	(void)minishell;
	signal(SIGQUIT, handler_sigquit);
	signal(SIGINT, handler_sigint);
	return (true);
}
