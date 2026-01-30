/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:22:32 by thlibers          #+#    #+#             */
/*   Updated: 2026/01/30 14:26:05 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *old, size_t old_size, size_t new_size)
{
	size_t			smallest;
	unsigned char	*new;

	smallest = old_size;
	if (new_size < old_size)
		smallest = new_size;
	new = malloc(sizeof(char) * (new_size + 1));
	if (!new)
		return (free(old), NULL);
	return (ft_memcpy(new, old, smallest), free(old), new);
}
