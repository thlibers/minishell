/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:47:36 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/30 16:56:14 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*path_builder(t_env *env, char *dir)
{
	char	*fullpath;
	char	*tmp_str;

	if (!dir && !ft_getenv(env, "HOME"))
		return (printf("cd: HOME not set\n"), NULL);
	else if(!dir)
		return (ft_getenv(env, "HOME"));
	if (dir[0] == '/')
	{
		fullpath = ft_strdup(dir);								// A changer car repart de la racine
		return (fullpath);										// sprintf ?
	}
	tmp_str = ft_strjoin(ft_getenv(env, "PWD"), "/");
	if (!tmp_str)
		return (NULL);
	fullpath = ft_strjoin(tmp_str, dir);
	if (!tmp_str)
		free(tmp_str);
	if (!fullpath)
		return (NULL);
	return (fullpath);
}

void pwd_update(t_minishell *minishell, char *new_path)
{
	t_env	*head;
	char 	*pwd_save;

	head = minishell->env;
	while (minishell->env)
	{
		if (strcmp(minishell->env->name, "PWD") == 0)
		{
			pwd_save = ft_strdup(minishell->env->value);
			if (minishell->env->value)
				free(minishell->env->value);
			minishell->env->value = ft_strdup(new_path);
		}
		minishell->env = minishell->env->next;					// A proteger
	}
	minishell->env = head;
	while (minishell->env)
	{
		if (strcmp(minishell->env->name, "OLDPWD") == 0)
		{
			if (minishell->env->value)
				free(minishell->env->value);
			minishell->env->value = ft_strdup(pwd_save);
		}
		minishell->env = minishell->env->next;
	}
	free (pwd_save);
	minishell->env = head;
}

//	PATH ABSOLUTE = 0 ; PATH RELATIVE = 1
char	*parsing_dir(t_minishell *minishell, char *dir)
{
	char	*new_path;

	new_path = path_builder(minishell->env, dir);
	if (!new_path)
		return (NULL);
	chdir(new_path);
	if (errno == ENAMETOOLONG)
		return (printf("cd: Path is too long"), free(new_path), NULL);
	else if (errno == ENOENT)
		ft_fprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", new_path);		// Gerer le uset OLDPWD. "cd: OLDPWD not set\n"
	else if (errno == ENOTDIR)
		printf("cd: '%s' is not a directory", dir);
	else if (errno == EACCES)
		printf("cd: Permission denied: '%s'\n", dir);
	else if (errno == ENOENT)
		printf("cd: The directory '%s' does not exist\n", dir);
	else if (errno == ELOOP)
		printf("cd: Too many lenvels of symbolic links\n");
	else
		pwd_update(minishell, new_path);
	if (new_path)
		free(new_path);
	return (NULL);
}

void	ft_cd(t_minishell *minishell, t_command *com_arg)
{
	int		i;
	char	*updated_pwd;
	
	i = 0;
	updated_pwd = NULL;
	if(!com_arg->arg_count || strcmp(com_arg->arguments[0], "~") == 0) 				// "cd ~/Exemple" a gerer
		parsing_dir(minishell, ft_getenv(minishell->env, "HOME"));
	else if(com_arg->arguments[0][0] == '.' && com_arg->arguments[0][1] == '.')
	{
		if(com_arg->arguments[0][2] == '/')
		{
			 updated_pwd = ft_strdup(ft_getenv(minishell->env, "PWD"));
			i = ft_strlen(updated_pwd) - 1;
			while (updated_pwd[i] != '/')
				i--;
			if (updated_pwd[i] == '/')												// Gerer "cd msh/source/.."
			{
				updated_pwd = ft_realloc(updated_pwd, ft_strlen(updated_pwd), i + ft_strlen(com_arg->arguments[0]) - 1);
				updated_pwd[i] = '\0';
				updated_pwd = ft_strjoin(updated_pwd, &com_arg->arguments[0][2]);
			}
			parsing_dir(minishell, updated_pwd);
		}
		else
		{
			updated_pwd = ft_strdup(ft_getenv(minishell->env, "PWD"));
			i = ft_strlen(updated_pwd) - 1;
			while (updated_pwd[i] != '/')
				i--;
			if (updated_pwd[i] == '/')
			{
				updated_pwd = ft_realloc(updated_pwd, ft_strlen(updated_pwd), i + 1);
				updated_pwd[i] = '\0';
			}
			parsing_dir(minishell, updated_pwd);
		}
		free (updated_pwd);
	}
	else if(strcmp(com_arg->arguments[0], "-") == 0)
	{
		parsing_dir(minishell, ft_getenv(minishell->env, "OLDPWD"));
	}
	else		// le path absolu et relatif.
	{
		edit_env(&minishell->env, "PWD", "NEW_PWD");
		//parsing_dir(minishell, com_arg->arguments[0]);	
	}
}

// Modifier la variable env "PWD",
//	si "cd .." suprimer le derner dossier du pwd (si c'est pas la racine)
// cd ~ et cd -

// cd ~ garde uniquement le home/
// cd - revient a l'ancien dossier ($OLDPWD)
// par exemple (dans msh "cd source/utils" puis "cd -" pour revenir dans msh)

// home/minishell/sources			utiliser "chdir" pour maj notre position.
// cd ../FOLDER a gerer aussi

// deux chdir a faire (un qui revient en arriere et un qui va dans le nouveau dossier)
//
// BUG :
// 1 -	DOUBLE FREE
//		cd ..
//		cd aze
// 2 -	DOUBLE FREE
//		cd ~
//		cd ..
//		cd ~
//		CTRL + D
