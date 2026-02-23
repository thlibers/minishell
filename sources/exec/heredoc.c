/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 09:00:43 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/23 17:52:58 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*get_line(void)
{
	char	*buff;
	char	*line;
	int		bytes_read;

	bytes_read = 1;
	line = NULL;
	buff = ft_calloc(10 + 1, sizeof(char));
	if (!buff)
		return (NULL);
	while (!ft_strchr(buff, '\n') && bytes_read > 0)
	{
		bytes_read = read(0, buff, 10);
		if (bytes_read < 0)
		{
			if (buff)
				free(buff);
		}
		buff[bytes_read] = '\0';
		line = ft_strfreejoin(line, buff);
		if (!line)
			return (free(buff), NULL);
	}
	free(buff);
	return (line);
}

static int	heredoc_init(t_exec *exec)
{
	if (exec->infile_fd > 2)
		close(exec->infile_fd);
	exec->infile_fd = open(HEREDOC_F, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (exec->infile_fd < 0)
	{
		cleanup_pipex(exec);
		ft_fprintf(STDERR_FILENO, "Failed to open/create/erase tmp file");
		return (0);
	}
	return (1);
}

int	here_doc(t_exec *exec)
{
	char	*line;

	line = NULL;
	if (!heredoc_init(exec))
		return (1);
	while (1)
	{
		if (line)
			free(line);
		write(1, "> ", 2);
		line = get_line();
		if (!line)
		{
			cleanup_pipex(exec);
			ft_fprintf(STDERR_FILENO, "Heredoc failed");
			return (1);
		}
		if (ft_strnstr(line, exec->limiter, ft_strlen(line)))
			break ;
		ft_putstr_fd(line, exec->infile_fd);
	}
	close(exec->infile_fd);
	exec->infile_fd = open("/tmp/pipex_heredoc.tmp", O_RDONLY);
	if (exec->infile_fd < 0)
	{
		ft_fprintf(STDERR_FILENO, "Failed to reopen heredoc file for reading");
		return (1);
	}
	free(line);
	return (0);
}
