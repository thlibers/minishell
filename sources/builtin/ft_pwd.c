/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:23:52 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/20 17:39:15 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_pwd(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strncmp(env->name, "PWD", strlen(env->name)))
		{
			printf("%s\n", env->value);
			return (0);
		}
		i++;
	}
	return (1);
}
