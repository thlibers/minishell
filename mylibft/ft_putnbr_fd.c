/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:40:48 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/16 17:19:54 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_fd(int n, int fd)
{
	int	size;

	size = 0;
	if (n == -2147483648)
		size += ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		size += ft_putchar_fd('-', fd);
		size += ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		size += ft_putnbr_fd(n / 10, fd);
		size += ft_putchar_fd(n % 10 + '0', fd);
	}
	else
		size += ft_putchar_fd(n + '0', fd);
	return (size);
}

// int main()
// {
// 	ft_putnbr_fd(123456, 1);
// 	ft_putchar_fd('\n', 1);
// 	ft_putnbr_fd(-2147483648, 1);
// }