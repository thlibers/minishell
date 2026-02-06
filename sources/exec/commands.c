/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:20:34 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/06 16:28:32 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**get_path_from_env(t_exec *exec)
{
	int		i;
	char	*path_line;
	char	**path;

	if (!exec->env)
		return (NULL);
	i = 0;
	while (exec->env[i])
	{
		if (ft_strncmp(exec->env[i], "PATH=", 5) == 0)
		{
			path_line = exec->env[i] + 5;
			path = ft_split(path_line, ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

static char	*build_path(char *cmd, char **paths)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_array(paths), NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (free_array(paths), NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(t_exec *exec, char *cmd)
{
	char	**path;
	char	*full_path;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = get_path_from_env(exec->env);
	if (!path)
		return (NULL);
	full_path = build_path(cmd, path);
	return (free_array(path), full_path);
}
