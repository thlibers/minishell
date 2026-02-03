/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:47:36 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/03 18:13:49 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*path_builder(t_env *env, char *dir)
{
	char	*fullpath;
	char	*tmp_str;

	if (!dir && !ft_getenv(env, "HOME"))
		return (printf("cd: HOME not set\n"), NULL);			// (OLPWD et HOME) A dissocier
	else if (!dir && !ft_getenv(env, "OLDPWD"))
		return (printf("cd: OLDPWD not set\n"), NULL);
	else if(!dir)
		return (ft_getenv(env, "HOME"));
	if (dir[0] == '/')
	{
		fullpath = ft_strdup(dir);
		return (fullpath);
	}
	tmp_str = ft_strjoin(ft_getenv(env, "PWD"), "/");
	if (!tmp_str)
		return (NULL);
	fullpath = ft_strjoin(tmp_str, dir);
	if (!fullpath)
		return (NULL);
	return (fullpath);
}

char	*parsing_dir(t_minishell *minishell, char *dir)
{
	char	*new_path;

	new_path = path_builder(minishell->env, dir);
	if (!new_path)
		return (NULL);
	chdir(new_path);
	if (errno == ENAMETOOLONG)
		printf("cd: Path is too long");
	else if (errno == ENOENT)
		ft_fprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", new_path);
	else if (errno == ENOTDIR)
		printf("cd: '%s' is not a directory\n", dir);
	else if (errno == EACCES)
		printf("cd: Permission denied: '%s'\n", dir);
	else if (errno == ENOENT)
		printf("cd: The directory '%s' does not exist\n", dir);
	else if (errno == ELOOP)
		printf("cd: Too many lenvels of symbolic links\n");
	else
		edit_env(&minishell->env, "PWD", new_path);
	 if (new_path)
	 	free(new_path);
	return (NULL);
}

static void	cd_dotdotslash(t_minishell *minishell, t_command *com_arg)
{
	int		i;
	int		pos;
	char	*updated_pwd;

	if (com_arg->arguments[0][0] == '/')
	{
		updated_pwd = ft_strdup(com_arg->arguments[0]);
	}
	else
	{
		updated_pwd = ft_strjoin(ft_getenv(minishell->env, "PWD"), "/");		// sprintf ?
		updated_pwd = ft_strjoin(updated_pwd, com_arg->arguments[0]);
	}
	printf("PWD = %s\n", updated_pwd);
	if (!updated_pwd)
		return ;
	i = ft_strlen(updated_pwd) - 1;
	while (i >= 0)
	{
		while (!ft_strnstr(&updated_pwd[i], "../", 3) && i >= 0)
			i--;
		if ( i < 0)
			break ;
		if (updated_pwd[i] == '.')
		{
			ft_strcat(&updated_pwd[i], &updated_pwd[i + 3]);
			printf("PWD cat1 = %s\n", updated_pwd);
			pos = i;
			i--;
			while (updated_pwd[i - 1] != '/')
				i--;
			ft_strcat(&updated_pwd[i], &updated_pwd[pos]);
			printf("PWD cat2 = %s\n", updated_pwd);
		}
		i--;
	}
	pos = ft_strlen(updated_pwd);
	updated_pwd = ft_realloc(updated_pwd, ft_strlen(updated_pwd));
	updated_pwd[pos] = '\0';
	parsing_dir(minishell, updated_pwd);
	free(updated_pwd);
}

static void	cd_dotdot(t_minishell *minishell)
{
	int		i;
	char	*updated_pwd;

	updated_pwd = ft_strdup(ft_getenv(minishell->env, "PWD"));
	i = ft_strlen(updated_pwd) - 1;
	while (updated_pwd[i] != '/')
		i--;
	if (updated_pwd[i] == '/')
	{
		updated_pwd = ft_realloc(updated_pwd, i + 1);
		if (i == 0)
			updated_pwd[i + 1] = '\0';
		else
			updated_pwd[i] = '\0';
	}
	parsing_dir(minishell, updated_pwd);
	free(updated_pwd);
}

void	ft_cd(t_minishell *minishell, t_command *com_arg)
{
	int		arg_len;

	arg_len = ft_strlen(com_arg->arguments[0]);
	if(com_arg->arg_count == 0 || strcmp(com_arg->arguments[0], "~") == 0) 				// "cd ~/Exemple" a gerer (expand)
		parsing_dir(minishell, ft_getenv(minishell->env, "HOME"));
	if(com_arg->arguments[0][arg_len - 1] == '/' && arg_len > 1)
		com_arg->arguments[0][arg_len - 1] = '\0';
	if(ft_strnstr(com_arg->arguments[0], "..", arg_len))
	{
		if(ft_strnstr(com_arg->arguments[0], "../", arg_len))							// Gerer le cd ../..
		{
			cd_dotdotslash(minishell, com_arg);
		}
		else if (com_arg->arguments[0][2] == '\0')
			cd_dotdot(minishell);
	}
	else if(strcmp(com_arg->arguments[0], "-") == 0)
		parsing_dir(minishell, ft_getenv(minishell->env, "OLDPWD"));
	else
		parsing_dir(minishell, com_arg->arguments[0]);
}
