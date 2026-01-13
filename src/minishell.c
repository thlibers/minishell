/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:44:45 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/04 21:44:46 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"


bool  init_minishell(t_minishell *minishell, char **envp)
{
	memset(minishell, 0, sizeof(t_minishell));
	if (!minishell)
		return (false);
	if (!init_ev(&minishell->ev, envp))
		return (false);
	return (true);
}

int main(int argc, char **argv, char **envp)
{
	int			status = 0;
	t_minishell	minishell;
	
	if (!init_minishell(&minishell, envp))
		return (1);
	env(minishell);
	while (1)
	{
		prompt();
		//free(minishell->token);
	}
	return (0);
}

