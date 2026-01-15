/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:07:24 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/15 17:49:23 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	init_history(t_minishell *minishell)
{
	char *line;

	minishell->fd_history = open(MSH_HIST, O_RDWR | O_CREAT, 0644);
	if (!minishell->fd_history)
	{
		return (1);
	}
	while(line)
	{
		line = get_next_line(minishell->fd_history);
		add_history(line);
		free(line);
	}
	return (0);
}

int	add_to_history(int fd, char *line)
{
	int size;
	
	if (!line)
		return (1);
	add_history(line);
	size = write(fd, line, ft_strlen(line));
	if (!size || size < 0)
	{
		return (1);
	}
	return (0);
}
