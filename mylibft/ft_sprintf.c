/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:26:49 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/11 11:27:04 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"




int ft_sprintf(char *str, char *format, ...)
{
	int i;
	int count;
	va_list list;

	i = 0;
	count = 0;
	va_start(list, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			
	}
	va_end(list);
	return (count);
}
