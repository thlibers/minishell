/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 09:00:43 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/16 08:16:38 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <unistd.h>

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
	write(exec->files.hd_fd[exec->files.hd_fd_size], tok->str,
		ft_strlen(tok->str));
	write(exec->files.hd_fd[exec->files.hd_fd_size], "\n", 1);
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
	close(exec->files.hd_fd[exec->files.hd_fd_size]);
	exec->files.hd_fd[exec->files.hd_fd_size] = -1;
	clean_all(minishell);
	exit(0);
}
