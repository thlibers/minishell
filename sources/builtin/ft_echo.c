/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 09:33:32 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/29 15:33:45 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv)
{
	bool	new_line;
	int		i;

	i = 1;
	new_line = true;
	if (argc == 1)
		return (ft_putchar_fd('\n', 1), 0);
	if (ft_strncmp(argv[1], "-n", 2) == 0 && ft_strlen(argv[1]) == 2)
		new_line = false;
	while (argv[i])
	{
		if ((i == 1 && new_line) || i >= 2)
		{
			ft_putstr_fd(argv[i], 1);
			if ((i + 1) != argc)
				ft_putchar_fd(' ', 1);
		}
		i++;
	}
	if (new_line == true)
		ft_putchar_fd('\n', 1);
	return (0);
}

// Gerer le echo -n.
