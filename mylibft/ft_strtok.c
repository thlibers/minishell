/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:54:52 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/26 17:03:40 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_isset(char c, const char *set)
{
	while (set && c != *set)
		set++;
	return (c == *set);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*s;
	char		*ret;

	if (str)
		s = str;
	if (!s || !*s)
		return (NULL);
	ret = s;
	while (*s && ft_isset(*s, delim))
	{
		s++;
		ret++;
	}
	while (*s && !ft_isset(*s, delim))
		s++;
	if (*s && ft_isset(*s, delim))
		*(s++) = 0;
	return (ret);
}
