/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:05:28 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/20 17:08:30 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_export_arg(t_minishell *minishell, char *str)
{
	t_env	*head;
	char	**tab;
	int		status;
	
	head = minishell->env;
	tab = env_spliter(str);
	if (!tab)
		return(1);
	status = 0;
	while(minishell->env && status == 0)
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
		ft_envadd_back(minishell->env, ft_envnew(tab[1]));
	minishell->env = head;
	return (0);
}

int	ft_export_p(t_minishell *minishell, char *str)
{
	t_env	*head;
	char	**tab;
	int		status;
	
	head = minishell->env;
	tab = env_spliter(str);
	if (!tab)
		return(1);
	status = 0;
	while(minishell->env && status == 0)
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
		ft_envadd_back(minishell->env, ft_envnew(tab[1]));
	minishell->env = head;
	return (0);
}


// traiter le -p (print) sensiblement la meme chose que export sans arguments.
// la commande export renevoie TOUTES les variables d'env avec leur valeurs ou sans.