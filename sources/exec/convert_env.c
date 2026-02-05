/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 15:29:09 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/05 17:22:40 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_envsize(t_env *env)
{
	int		count;
	t_env	*tmp;

	if (!env)
		return (0);
	tmp = env;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

char	**convert_env(t_env *env)
{
	int		i;
	char	*tmp;
	char	**converted_tab;

	i = 0;
	converted_tab = malloc(sizeof(char *) * ft_envsize(env) + 1);
	while (env->next)
	{
		tmp = ft_strjoin(env->name, "=");
		converted_tab[i] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
		i++;
	}
	converted_tab[i] = NULL;
	return (converted_tab);
}

// le free quand appel0