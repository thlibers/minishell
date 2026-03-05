/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:22:02 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/05 19:20:24 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	dot_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] == '.')
			count++;
		i++;
	}
	return (count);
}

int	dot_skip(char *new_pwd, int i)
{
	while (new_pwd[i] && ft_strncmp(&new_pwd[i], "..", 2) != 0)
		i++;
	while (new_pwd[i] && new_pwd[i] == '.' && new_pwd[i] != '/')
		i++;
	if (new_pwd[i] == '/')
		i++;
	return (i);
}

static char	*path_builder(t_env *env, char *dir)
{
	char	*fullpath;
	char	*tmp_str;
	char	pwd_buffer[4096];

	if ((!dir || dir[0] == '\0') && !ft_getenv(env, "HOME"))
		return (printf("cd: HOME not set\n"), NULL);
	else if (!dir && !ft_getenv(env, "OLDPWD"))
		return (printf("cd: OLDPWD not set\n"), NULL);
	else if (!dir)
		return (ft_getenv(env, "HOME"));
	if (dir[0] == '/')
	{
		fullpath = ft_strdup(dir);
		return (fullpath);
	}
	if (ft_strlen(getcwd(pwd_buffer, sizeof(pwd_buffer))) == 1)
	{
		fullpath = ft_strjoin("/", dir);
		return (fullpath);
	}
	tmp_str = ft_strjoin(getcwd(pwd_buffer, sizeof(pwd_buffer)), "/");
	if (!tmp_str)
		return (NULL);
	fullpath = ft_strjoin(tmp_str, dir);
	return (free(tmp_str), fullpath);
}

char	*parsing_dir(t_minishell *minishell, char *dir)
{
	char	*new_path;

	new_path = path_builder(minishell->env, dir);
	if (!new_path)
		return (NULL);
	chdir(new_path);
	if (errno == ENAMETOOLONG)
		ft_fprintf(2, "cd: Path is too long");
	else if (errno == ENOENT)
		ft_fprintf(2, "cd: %s: No such file or directory\n", new_path);
	else if (errno == ENOTDIR)
		ft_fprintf(2, "cd: '%s' is not a directory\n", dir);
	else if (errno == EACCES)
		ft_fprintf(2, "cd: Permission denied: '%s'\n", dir);
	else if (errno == ENOENT)
		ft_fprintf(2, "cd: The directory '%s' does not exist\n", dir);
	else if (errno == ELOOP)
		ft_fprintf(2, "cd: Too many lenvels of symbolic links\n");
	else
		edit_env(&minishell->env, "PWD", new_path);
	if (new_path)
		free(new_path);
	if (errno > 0)
		return (minishell->exit_code = 1, NULL);
	return (minishell->exit_code = 0, NULL);
}
