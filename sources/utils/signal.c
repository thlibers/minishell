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

bool  init_signal(t_minishell *minishell)
{
	ft_memset(&minishell->sa)
	if (sigemptyset(&minishell->sa.sa_mask) == -1)
		return (false);
	if (!sigaddset(&minishell->sa, SA_SIGQUIT))
		return (false);
	minishell->sa.sa_flags = SA_SIGINFO;
	minishell->sa.sa_handler = NULL;
	sigaction(SA_SIGINT, &minishell->sa, NULL);		// Ignore SIGQUIT signal
}
