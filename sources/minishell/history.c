/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:07:24 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/16 14:59:56 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	init_history(t_minishell *minishell)
{
	char	*line;
	char	*backn;

	line = NULL;
	minishell->fd_history = open(MSH_HIST, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (!minishell->fd_history)
	{
		ft_fprintf(STDERR_FILENO,
			"\e[0;31mFailed to open the file history\e[0m");
		return (0);
	}
	line = get_next_line(minishell->fd_history);
	while (line)
	{
		backn = ft_strrchr(line, '\n');
		if (backn)
			line[backn - line] = '\0';
		add_history(line);
		free(line);
		line = get_next_line(minishell->fd_history);
	}
	return (1);
}

int	add_to_history(int fd, char *line)
{
	int	size;

	if (!line)
		return (1);
	add_history(line);
	size = write(fd, line, ft_strlen(line));
	if (!size || size < 0)
	{
		ft_fprintf(STDERR_FILENO, "\e[0;31mFailed write on history file\e[0m");
		return (1);
	}
	else if (size)
	{
		size = write(fd, "\n", 1);
		if (!size || size < 0)
		{
			ft_fprintf(STDERR_FILENO,
				"\e[0;31mFailed write on history file\e[0m");
			return (1);
		}
	}
	return (0);
}
