/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 15:46:29 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/22 16:29:49 by thlibers         ###   ########.fr       */
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
		clear_token(&minishell.token);
	}
	ft_clear(&minishell);
	return (0);
}
