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


t_minishell	*init_minishell(t_minishell *minishell, char **envp)
{
	memset(minishell, 0, sizeof(t_minishell));
	if (!minishell)
		return (NULL);
	if (!init_ev(&minishell->ev, envp));
		return (NULL);
	return (minishell);
}

int main(int argc, char **argv, char **envp)
{
	int			status = 0;
	t_minishell	minishell;
	
	init_minishell(&minishell, envp);
	while (1)
	{
		env(minishell);
		prompt();
		//free(minishell->token);
	}
	return (0);
}

