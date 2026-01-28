/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:47:36 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/28 16:43:17 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*path_builder(t_env *env, char *dir)
{
	char	*fullpath;
	char	*tmp_str;

	if (!dir && !ft_getenv(env, "HOME"))
		return (printf("cd: HOME not set\n"), NULL);
	if (dir[0] == '/')
	{
		fullpath = ft_strdup(dir);
		return (fullpath);
	}
	// A changer car repart de la racine
	// sprintf ?
	tmp_str = ft_strjoin(ft_getenv(env, "PWD"), "/");
	if (!tmp_str)
		return (NULL);
	fullpath = ft_strjoin(tmp_str, dir);
	free(tmp_str);
	if (!fullpath)
		return (NULL);
	return (fullpath);
}


//	PATH ABSOLUTE = 0 ; PATH RELATIVE = 1
char	*parsing_dir(t_env *env, char *dir)
{
	char	*new_path;

	new_path = path_builder(env, dir);
	if (!new_path)
		return (NULL);
	chdir(new_path);
	if (errno == ENAMETOOLONG)
		return (printf("cd: Path is too long"), free(new_path), NULL);
	else if (errno == ENOENT)
		return (ft_fprintf(STDERR_FILENO ,"cd: %s: No such file or directory\n", new_path), free(new_path), NULL);
	else if (errno == ENOTDIR)
		return (printf("cd: '%s' is not a directory", dir), free(new_path),
			NULL);
	else if (errno == EACCES)
		return (printf("cd: Permission denied: '%s'\n", dir), NULL);
	else if (errno == ENOENT)
		return (printf("cd: The directory '%s' does not exist\n", dir), NULL);
	else if (errno == ELOOP)
		return (printf("cd: Too many lenvels of symbolic links\n"),
			free(new_path), NULL);
	return (new_path);
}

void	ft_cd(t_env *env, char *arg)
{
	
}

// Modifier la variable env "PWD", si "cd .." suprimer le derner dossier du pwd (si c'est pas la racine)
// cd ~ et cd -

//cd ~ garde uniquement le home/
// cd - revient a l'ancien dossier 
// par exemple (dans msh "cd source/utils" puis "cd -" pour revenir dans msh)

// home/minishell/sources			utiliser "chdir" pour maj notre position.
// cd ..




// int	main(int argc, char **argv)
// {
// 	char	*path;

// 	if (argc > 2)
// 		return (ft_putstr_fd("Too many args for cd command", 1), 1);
// 	path = parsing_dir(argv[1]);
// 	if (!path)
// 		return (1);
// }
