/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:28 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/27 15:34:24 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Manque :
//	- Check caracteres valides
//	- Gerer les export +=
//	- Gerer les multiple export en une command
//  -

static int	check_valarg(char **tab)
{
	int	i;

	i = 0;
	if (isdigit(tab[0][0]))
	{
		ft_fprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n",
			tab[0]);
		return (0);
	}
	while (tab[0][i])
	{
		if (!isalnum(tab[0][i]) && tab[0][i] != '_')
		{
			ft_fprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n",
				tab[0]);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	ft_export_arg(t_minishell *minishell, t_exec *exec)
{
	t_env	*head;
	char	**tab;
	int		status;

	head = minishell->env;
	tab = env_spliter(exec->cmd[1]); // A adapter pour plusieurs args
	if (!tab || !check_valarg(tab))
		return (minishell->exit_code = 1, 1);
	status = 0;
	while (minishell->env && status == 0)
	{
		if (strcmp(minishell->env->name, tab[0]) == 0)
		{
			if (minishell->env->value)
				free(minishell->env->value);
			minishell->env->value = ft_strdup(tab[1]);
			status = 1;
		}
		minishell->env = minishell->env->next;
	}
	minishell->env = head;
	if (status == 0)
		add_env_back(&minishell->env, create_env_var(tab[0], tab[1],
				ft_strchr(exec->cmd[1], '=')));
	minishell->exit_code = 0;
	return (free_tab(tab), 0);
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
		cpy = cpy->next;
	}
	env_clean(save, NULL);
	minishell->exit_code = 0;
}

void	ft_export(t_minishell *minishell, t_exec *exec, int child_number)
{
	init_child(exec, child_number, 0);
	if (exec->argc == 0)
		ft_export_noarg(minishell);
	else
		ft_export_arg(minishell, exec);
}

// Exemple : export abc=def ghi=ggg