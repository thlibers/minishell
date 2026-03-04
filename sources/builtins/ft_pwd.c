/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:23:52 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/04 13:13:18 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_pwd(t_minishell *minishell, int child_number)
{
	char	pwd_buffer[4096];

	init_child(&minishell->exec, child_number, 0);
	if (getcwd(pwd_buffer, sizeof(pwd_buffer)))
	{
		printf("%s\n", pwd_buffer);
		return (0);
	}
	else
		ft_fprintf(STDERR_FILENO, "pwd error");
	return (1);
}
