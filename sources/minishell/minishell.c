/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:44:45 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/15 15:49:39 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool  init_minishell(t_minishell *minishell, char **envp)
{
	memset(minishell, 0, sizeof(t_minishell));
	if (!minishell)
		return (false);
	if (!init_ev(&minishell->ev, envp))
		return (false);
	return (true);
}
