/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:11 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/03 16:15:34 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

bool	prompt(t_minishell *minishell)
{
	char	*line;

	if (minishell->tty)
		line = readline(F_GREEN "minishell > " RESET);
	else
	{
		line = readline("");
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (!line)
		return (false);
	line = ft_strtrim(line, " ");
	if (line && line[0])
	{
		add_to_history(minishell->fd_history, line);
		minishell->tok = tokenizer(line);
		if (!minishell->tok)
			return (free(line), true);
		ft_expand(minishell, minishell->env, &minishell->tok);
		minishell->ast = create_tree(minishell->tok, 0);
		free_tok(&minishell->tok);
	}
	free(line);
	return (true);
}
