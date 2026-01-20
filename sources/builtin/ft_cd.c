/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:47:36 by nclavel           #+#    #+#             */
/*   Updated: 2025/12/11 17:41:46 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/program/cd.h"

char	*path_builder(char *dir)
{
	char	*fullpath;
	char	*tmp_str;

	if (ft_strchr(dir, '/') != 0)
	{
		fullpath = ft_strdup(dir);
		return (fullpath);
	}
	tmp_str = ft_strjoin(getenv("PWD"), "/");
	if (!tmp_str)
		return (NULL);
	fullpath = ft_strjoin(tmp_str, dir);
	free(tmp_str);
	if (!fullpath)
		return (NULL);
	return (fullpath);
}

//	PATH ABSOLUTE = 0 ; PATH RELATIVE = 1
char	*parsing_dir(char *dir)
{
	char	*new_path;

	new_path = path_builder(dir);
	if (!new_path)
		return (NULL);
	chdir(new_path);
	if (errno == ENAMETOOLONG)
		return (printf("cd: Path is too long"), free(new_path), NULL);
	if (errno == ENOTDIR)
		return (printf("cd: '%s' is not a directory", dir), free(new_path),
			NULL);
	if (errno == EACCES)
		return (printf("cd: Permission denied: '%s'\n", dir), NULL);
	if (errno == ENOENT)
		return (printf("cd: The directory '%s' does not exist\n", dir), NULL);
	if (errno == ELOOP)
		return (printf("cd: Too many levels of symbolic links\n"),
			free(new_path), NULL);
	return (new_path);
}

int	main(int argc, char **argv)
{
	char	*path;
	
	if (argc > 2)
		return (ft_putstr_fd("Too many args for cd command", 1), 1);
	path = parsing_dir(argv[1]);
	if (!path)
		return (1);
	
}
