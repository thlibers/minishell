/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:28 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/06 07:50:14 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static char	**ft_select_tab(t_minishell *minishell, t_exec *exec, char **tab,
		int i)
{
	if (ft_strnstr(exec->cmd[i], "+=", ft_strlen(exec->cmd[i])))
		tab = add_to_envvalue(minishell, exec, i);
	else
		tab = env_spliter(exec->cmd[i]);
	return (tab);
}

static void	ft_value_treatement(t_minishell *minishell, char **tab, int *status)
{
	while (minishell->env && *status == 0)
	{
		if (strcmp(minishell->env->name, tab[0]) == 0)
		{
			if (minishell->env->value && tab[1] && tab[1][0] != '\0')
				free(minishell->env->value);
			if (tab[1] && tab[1][0] != '\0')
			{
				minishell->env->value = ft_strdup(tab[1]);
				minishell->env->equal = 1;
			}
			*status = 1;
		}
		minishell->env = minishell->env->next;
	}
}

static int	ft_export_arg(t_minishell *minishell, t_exec *exec, bool pipe)
{
	t_env	*head;
	char	**tab;
	int		status;
	int		i;

	if (pipe == true)
		return (1);
	head = minishell->env;
	i = 1;
	while (exec->cmd[i])
	{
		tab = ft_select_tab(minishell, exec, tab, i);
		if (!check_env_name(minishell, tab, &i))
		{
			ptr_free_tab(&tab);
			continue ;
		}
		status = 0;
		ft_value_treatement(minishell, tab, &status);
		minishell->env = head;
		if (status == 0)
			add_env_back(&minishell->env, create_env_var(tab[0], tab[1],
					ft_strchr(exec->cmd[i], '=')));
		i++;
		ptr_free_tab(&tab);
	}
	// ptr_free_tab(&tab);
	return (minishell->exit_code = 0, 0);
}

static void	ft_export_noarg(t_minishell *minishell)
{
	t_env	*cpy;
	t_env	*save;

	cpy = env_cpy(minishell->env);
	sort_env(&cpy);
	save = cpy;
	while (cpy)
	{
		if (cpy->value && cpy->equal)
			printf("export %s=%s\n", cpy->name, cpy->value);
		else if (!cpy->value && cpy->equal)
			printf("export %s=\n", cpy->name);
		else
			printf("export %s\n", cpy->name);
		cpy = cpy->next;
	}
	env_clean(save, NULL);
	minishell->exit_code = 0;
}

void	ft_export(t_minishell *minishell, t_exec *exec, int child_number,
		bool pipe)
{
	init_child(exec, child_number, 0);
	if (exec->argc == 0)
		ft_export_noarg(minishell);
	else
		ft_export_arg(minishell, exec, pipe);
}
