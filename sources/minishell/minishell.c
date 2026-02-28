/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:44:45 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/20 15:14:27 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	init_minishell(t_minishell *minishell, char **envp)
{
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->tty = isatty(ttyslot());
	if (!init_history(minishell))
		return (false);
	if (!init_env(&minishell->env, envp))
		return (false);
	init_signal();
	return (true);
}
