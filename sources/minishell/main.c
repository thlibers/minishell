/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:46:29 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/27 15:08:34 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	if (!init_minishell(&minishell, envp))
		return (1);
	while (1)
	{
		if (!prompt(&minishell))
			break ;
		if (minishell.ast)
		{
			execution(&minishell);
			cleanup_pipe(&minishell, &minishell.exec);
			free_ast(&minishell.ast);
		}
	}
	ft_clear(&minishell);
	return (0);
}
