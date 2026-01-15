/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:44:45 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/15 17:30:48 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool  init_minishell(t_minishell *minishell, char **envp)
{
	memset(minishell, 0, sizeof(t_minishell));
	if (!init_history(minishell))
		return (false);
	if (!init_ev(&minishell->ev, envp))
		return (false);
	return (true);
}
