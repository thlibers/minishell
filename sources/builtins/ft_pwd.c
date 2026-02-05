/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:23:52 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/05 13:56:49 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*pwd;

	pwd = ft_getenv(env, "PWD");
	if (pwd)
	{
		printf("%s\n", pwd);
		return (0);
	}
	return (1);
}
