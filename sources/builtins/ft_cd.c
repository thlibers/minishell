/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:47:36 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/27 15:11:55 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	*parsing_dir(t_minishell *minishell, char *dir)
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

static char	*init_newpwd(t_minishell *minishell, t_exec *exec)
{
	char	*pwd;
	char	*new_pwd;

	if (exec->cmd[1][0] == '/')
		new_pwd = ft_strdup(exec->cmd[1]);
	else
	{
		pwd = malloc(sizeof(char) * ft_strlen(ft_getenv(minishell->env,
						"PWD")));
		pwd = ft_strjoin(ft_getenv(minishell->env, "PWD"), "/");
		new_pwd = ft_strjoin(pwd, exec->cmd[1]);
		free(pwd);
	}
	new_pwd[ft_strlen(new_pwd)] = '\0';
	return (new_pwd);
}

static int	dot_skip(char *new_pwd, int i)
{
	while (new_pwd[i] && ft_strncmp(&new_pwd[i], "..", 2) != 0)
		i++;
	while (new_pwd[i] && new_pwd[i] == '.' && new_pwd[i] != '/')
		i++;
	if (new_pwd[i] == '/')
		i++;
	return (i);
}

static char	*ft_dotdot(t_minishell *minishell, t_exec *exec)
{
	int		i;
	int		oldf_pos;
	int		count;
	char	*new_pwd;

	new_pwd = init_newpwd(minishell, exec);
	count = dotcount(new_pwd);
	while (count > 0)
	{
		i = 0;
		while (new_pwd[i] && ft_strncmp(&new_pwd[i + 1], "..", 2) != 0)
			i++;
		while (new_pwd[i - 1] != '/')
			i--;
		oldf_pos = i;
		i = dot_skip(new_pwd, i);
		if (oldf_pos == 1 || new_pwd[i] != '\0')
			ft_strcat(&new_pwd[oldf_pos], &new_pwd[i]);
		else
			ft_strcat(&new_pwd[oldf_pos - 1], &new_pwd[i]);
		count--;
	}
	return (new_pwd);
}

void	ft_cd(t_minishell *minishell, t_exec *exec, int child_number)
{
	int		arg_len;
	char	*updated_pwd;

	init_child(exec, child_number, 0);
	arg_len = ft_strlen(exec->cmd[1]);
	if (exec->argc == 0 || strcmp(exec->cmd[1], "~") == 0)
		parsing_dir(minishell, ft_getenv(minishell->env, "HOME"));
	if (exec->argc > 0)
	{
		if (exec->argc > 0 && exec->cmd[1][arg_len - 1] == '/'
			&& arg_len > 1)
			exec->cmd[1][arg_len - 1] = '\0';
		if (strcmp(exec->cmd[1], "-") == 0)
			parsing_dir(minishell, ft_getenv(minishell->env, "OLDPWD"));
		else if (ft_strnstr(exec->cmd[1], "..", arg_len))
		{
			updated_pwd = ft_dotdot(minishell, exec);
			parsing_dir(minishell, updated_pwd);
			free(updated_pwd);
		}
		else
			parsing_dir(minishell, exec->cmd[1]);
	}
}

// "cd ~/Exemple" a gerer (expand)
