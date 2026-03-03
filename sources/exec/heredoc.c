/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 09:00:43 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/25 13:27:50 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	heredoc_init(t_exec *exec)
{
	if (exec->infile_fd > 2)
		close(exec->infile_fd);
	exec->infile_fd = open(HEREDOC_F, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (exec->infile_fd < 0)
	{
		ft_fprintf(STDERR_FILENO, "Failed to open/create/erase tmp file");
		return (0);
	}
	return (1);
}

static t_tok	*line_to_tok(char *line, t_minishell *minishell)
{
	t_tok	*tok;
	int		i;

	i = 0;
	tok = ft_calloc(1, sizeof(t_tok));
	if (!tok)
		return (ft_fprintf(2, ENOENOMEM), NULL);
	tok->prev = NULL;
	tok->next = NULL;
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
	write(minishell->exec.infile_fd, tok->str, ft_strlen(tok->str));
	write(minishell->exec.infile_fd, "\n", 1);
	free_tok(&tok);
	return (NULL);
}

static int	terminate_heredoc(char **line, t_exec *exec)
{
	close(exec->infile_fd);
	exec->infile_fd = open(HEREDOC_F, O_RDONLY);
	if (exec->infile_fd < 0)
	{
		ft_fprintf(STDERR_FILENO, "Failed to reopen heredoc file for reading");
		return (0);
	}
	free(*line);
	return (1);
}

int	here_doc(t_exec *exec, t_minishell *minishell)
{
	char	*line;

	line = NULL;
	if (!heredoc_init(exec))
		return (1);
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
			line_to_tok(line, minishell);
		free(line);
	}
	if (terminate_heredoc(&line, exec))
		return (1);
	return (0);
}
