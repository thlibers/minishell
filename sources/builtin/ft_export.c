/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:28 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/28 15:37:28 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Manque :
//	-Check caracteres valides

static int	check_valarg(char *arg)
{
	int	i;

	i = 0;
	if (isdigit(arg[0]))
	{
		ft_fprintf(STDERR_FILENO, "export: `%s': not a valid identifier", arg);
		return (0);
	}
	while (arg[i])
	{
		if (!isalnum(arg[i]) || arg[i] != '_')
		{
			ft_fprintf(STDERR_FILENO, "export: `%s': not a valid identifier",
				arg);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_arg(t_minishell *minishell, char *arg)
{
	t_env	*head;
	char	**tab;
	int		status;

	head = minishell->env;
	tab = env_spliter(arg);
	if (!tab || !check_valarg(arg))
		return (minishell->exit_code = 1, 1);
	status = 0;
	while (minishell->env && status == 0)
	{
		if (strcmp(minishell->env->name, tab[0]))
		{
			if (minishell->env->value)
				free(minishell->env->value);
			minishell->env->value = ft_strdup(tab[1]);
			status = 1;
		}
		minishell->env = minishell->env->next;
	}
	if (status == 0)
		add_env_back(&minishell->env, new_env_node(tab[0], tab[1]));
	minishell->env = head;
	minishell->exit_code = 0;
	free_tab(tab);
	return (0);
}

void	ft_export_noarg(t_minishell *minishell)
{
	t_env	*cpy;
	t_env	*save;

	cpy = env_cpy(minishell->env);
	sort_env(&cpy);
	save = cpy;
	while (cpy)
	{
		printf("export %s=%s\n", cpy->name, cpy->value);
		cpy = cpy->next;
	}
	env_clean(save, NULL);
	minishell->exit_code = 0;
}

void	ft_export(t_minishell *minishell, t_command *command)
{
	if (command->arg_count == 0)
		ft_export_noarg(minishell);
	else
		ft_export_arg(minishell, NULL);
}
