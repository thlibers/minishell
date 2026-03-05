/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:47:36 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/05 20:11:05 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/error.h"
#include "includes/minishell.h"
#include "mylibft/libft.h"

static char	*init_newpwd(t_exec *exec)
{
	char	*pwd;
	char	*new_pwd;
	char	pwd_buffer[4096];

	if (exec->cmd[1][0] == '/')
		new_pwd = ft_strdup(exec->cmd[1]);
	else
	{
		pwd = malloc(sizeof(char) * ft_strlen(getcwd(pwd_buffer, 
				sizeof(pwd_buffer))));
		pwd = ft_strjoin(getcwd(pwd_buffer, sizeof(pwd_buffer)), "/");
		new_pwd = ft_strjoin(pwd, exec->cmd[1]);
		free(pwd);
	}
	new_pwd[ft_strlen(new_pwd)] = '\0';
	return (new_pwd);
}

static char	*ft_dotdot(t_exec *exec)
{
	int		i;
	int		oldf_pos;
	int		count;
	char	*new_pwd;

	new_pwd = init_newpwd(exec);
	count = dot_count(new_pwd);
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

static void	ft_cd_arg(t_minishell *minishell, t_exec *exec)
{
	int		arg_len;
	char	*updated_pwd;

	arg_len = ft_strlen(exec->cmd[1]);
	if (exec->argc > 0 && exec->cmd[1][arg_len - 1] == '/' && arg_len > 1)
		exec->cmd[1][arg_len - 1] = '\0';
	if (strcmp(exec->cmd[1], "-") == 0)
	{
		printf("%s\n", ft_getenv(minishell->env, "OLDPWD"));
		parsing_dir(minishell, ft_getenv(minishell->env, "OLDPWD"));
	}
	else if (ft_strnstr(exec->cmd[1], "..", arg_len))
	{
		updated_pwd = ft_dotdot(exec);
		parsing_dir(minishell, updated_pwd);
		free(updated_pwd);
	}
	else
		parsing_dir(minishell, exec->cmd[1]);
}

int	ft_cd(t_minishell *minishell, t_exec *exec, int child_number)
{
	init_child(exec, child_number, 0);
	if (exec->argc > 1)
		return (ft_fprintf(2, ECDARGC));
	if (exec->argc == 0 || strcmp(exec->cmd[1], "~") == 0)
		parsing_dir(minishell, ft_getenv(minishell->env, "HOME"));
	if (exec->argc > 0)
		ft_cd_arg(minishell, exec);
	return (0);
}
