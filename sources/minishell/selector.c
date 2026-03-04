/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:02:55 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/04 12:54:23 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	ft_cd_selector(t_minishell *minishell, int i)
{
	if (!check_pipe(minishell->ast))
		ft_cd(minishell, &minishell->exec, i);
}

static void	ft_exit_selector(t_minishell *minishell, int i)
{
	if (!check_pipe(minishell->ast))
		ft_exit(minishell, &minishell->exec, i);
}

static void	ft_export_selector(t_minishell *minishell, int i)
{
	if (!check_pipe(minishell->ast))
		ft_export(minishell, &minishell->exec, i, false);
	else
		ft_export(minishell, &minishell->exec, i, true);
}

static void	ft_unset_selector(t_minishell *minishell, int i)
{
	if (!check_pipe(minishell->ast))
		ft_unset(minishell, &minishell->exec, i);
}

bool	selector(t_minishell *minishell, int i)
{
	if (ft_strcmp(minishell->exec.cmd[0], "cd") == 0)
		ft_cd_selector(minishell, i);
	else if (ft_strcmp(minishell->exec.cmd[0], "echo") == 0)
		ft_echo(minishell, &minishell->exec, i);
	else if (ft_strcmp(minishell->exec.cmd[0], "env") == 0)
		ft_env(minishell, i);
	else if (ft_strcmp(minishell->exec.cmd[0], "exit") == 0)
		ft_exit_selector(minishell, i);
	else if (ft_strcmp(minishell->exec.cmd[0], "export") == 0)
		ft_export_selector(minishell, i);
	else if (ft_strcmp(minishell->exec.cmd[0], "pwd") == 0)
		ft_pwd(minishell, i);
	else if (ft_strcmp(minishell->exec.cmd[0], "unset") == 0)
		ft_unset_selector(minishell, i);
	else
		return (false);
	if (minishell->exec.save_std[0] > 0 || minishell->exec.save_std[1] > 0)
	{
		dup2(minishell->exec.save_std[0], STDIN_FILENO);
		dup2(minishell->exec.save_std[1], STDOUT_FILENO);
	}
	return (true);
}
