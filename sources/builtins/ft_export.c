/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:28 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/03 13:40:06 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
		if (!ft_isalnum(tab[0][i]) && tab[0][i] != '_')
		{
			ft_fprintf(STDERR_FILENO, "export: `%s': not a valid identifier\n",
				tab[0]);
			return (0);
		}
		i++;
	}
	return (1);
}

static char **add_to_envvalue(t_minishell *minishell, t_exec *exec, int pos)
{
	int i;
	char *value;
	char **tab;

	i = 0;
	tab = ft_calloc(3, sizeof(char *));
	value = ft_strchr(exec->cmd[pos], '=');
	tab[0] = ft_calloc(ft_strlen(exec->cmd[pos]) - ft_strlen(value), sizeof(char));
	while (ft_strncmp(&exec->cmd[pos][i], "+=", 2) != 0)
	{
		tab[0][i] = exec->cmd[pos][i];
		i++;
	}
	tab[1] = ft_strjoin(ft_getenv(minishell->env, tab[0]), value + 1);
	return (tab);
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
		if (ft_strnstr(exec->cmd[i], "+=", ft_strlen(exec->cmd[i])))
			tab = add_to_envvalue(minishell, exec, i);
		else
			tab = env_spliter(exec->cmd[i]);
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
					ft_strchr(exec->cmd[i], '=')));
		i++;
	}
	return (minishell->exit_code = 0, free_tab(tab), 0);
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

// Manque :
//	- Gerer les export "+=" (ajoute ce qu'il y a apres le '=' a la variable d'env)
//			exemple :	"PATH+=abc" ajoute abc a la fin de PATH