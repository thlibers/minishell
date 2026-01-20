/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:23:52 by nclavel           #+#    #+#             */
/*   Updated: 2025/12/11 17:39:12 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/program/pwd.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	(void)argv;
	(void)argc;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PWD", 4))
		{
			return (printf("%s\n", &envp[i][4]), 0);
		}
		i++;
	}
	return (1);
}