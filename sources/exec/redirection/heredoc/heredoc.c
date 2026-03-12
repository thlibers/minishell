/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 09:00:43 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/12 15:52:40 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static t_tok	*line_to_tok(char *line, t_minishell *minishell, t_exec *exec)
{
	t_tok	*tok;
	int		i;

	i = 0;
	tok = ft_calloc(1, sizeof(t_tok));
	if (!tok)
		return (ft_fprintf(2, ENOENOMEM), NULL);
	tok->str = ft_strdup(line);
	if (!tok->str)
		return (ft_fprintf(2, ENOENOMEM), free(tok), NULL);
	while (tok->str[i])
	{
		if (tok->str[i] == '$')
		{
			if (!dollar_treatements(minishell, &tok, &i))
				continue ;
		}
		i++;
	}
	write(exec->heredoc.heredoc_fd[exec->heredoc.heredoc_fd_size], tok->str,
		ft_strlen(tok->str));
	write(exec->heredoc.heredoc_fd[exec->heredoc.heredoc_fd_size], "\n", 1);
	free_tok(&tok);
	return (NULL);
}

int	here_doc(t_exec *exec, t_minishell *minishell)
{
	char	*line;

	line = NULL;
	clean_heredoc(minishell);
	handler_heredoc();
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, exec->limiter) == 0)
		{
			if (!line)
				ft_fprintf(2,
					"Minishell: Here-document delimited by EOF (wanted `%s')\n",
					exec->limiter);
			break ;
		}
		else if (line && line[0] != '\0')
			line_to_tok(line, minishell, &minishell->exec);
		free(line);
	}
	close(exec->heredoc.heredoc_fd[exec->heredoc.heredoc_fd_size]);
	full_clean(minishell);
	exit(0);
}
