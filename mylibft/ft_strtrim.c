/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:47:36 by thlibers          #+#    #+#             */
/*   Updated: 2026/03/03 16:13:44 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;

	if (s1 == NULL && set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trim = ft_substr(s1, start, end - start);
	free(s1);
	return (trim);
}

// int main ()
// {
// 	char set[] = "|> <";
// 	char str[] = "echo 'hello world' |";
// 	char *trim = ft_strtrim(str, set);
// 	printf("%s", trim);
// 	return(0);
// }