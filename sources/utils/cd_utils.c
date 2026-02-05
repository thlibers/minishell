/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:22:02 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/05 12:38:04 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int		dotcount(char *str)
{
	int i;
	int count;
	
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
	if (ft_strlen(ft_getenv(env, "PWD")) == 1)
	{
		fullpath = ft_strjoin("/", dir);
		return (fullpath);
	}
	tmp_str = ft_strjoin(ft_getenv(env, "PWD"), "/");
	if (!tmp_str)
		return (NULL);
	fullpath = ft_strjoin(tmp_str, dir);
	return (free(tmp_str), fullpath);
}
