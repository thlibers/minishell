/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:51:09 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/12 15:36:34 by thlibers         ###   ########.fr       */
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

bool	check_env_name(t_minishell *minishell, char **tab, int *i)
{
	if (!tab || !check_valarg(tab))
	{
		free_tab(tab);
		minishell->exit_code = 1;
		(*i)++;
		return (false);
	}
	return (true);
}

char	**add_to_envvalue(t_minishell *minishell, t_exec *exec, int pos)
{
	int		i;
	char	*value;
	char	**tab;

	i = 0;
	tab = ft_calloc(3, sizeof(char *));
	value = ft_strchr(exec->child.cmd[pos], '=');
	tab[0] = ft_calloc(ft_strlen(exec->child.cmd[pos]) - ft_strlen(value),
			sizeof(char));
	while (ft_strncmp(&exec->child.cmd[pos][i], "+=", 2) != 0)
	{
		tab[0][i] = exec->child.cmd[pos][i];
		i++;
	}
	tab[1] = ft_strjoin(ft_getenv(minishell->env, tab[0]), value + 1);
	return (tab);
}
