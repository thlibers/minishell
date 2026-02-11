/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:46:00 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/10 12:43:52 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

size_t	ft_strlcpy_mod(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	return (len);
}

void	ft_expand(t_env *env, t_tok **token)
{
	int		i;
	int		y;
	int		in_quote;
	char	*expand;
	char	*env_value;
	t_tok	*head;

	head = (*token);
	while (*token)
	{
		if ((*token)->type == T_WORD)
		{
			i = 0;
			in_quote = 0;
			while ((*token)->str[i])
			{
				if ((*token)->str[i] == '\'' && in_quote == IN_RESET)
				{
					while ((*token)->str[i] && is_inquote(&in_quote,
							(*token)->str[i]) == IN_SINGLE_QUOTE)
						i++;
				}
				else
				{
					if ((*token)->str[i] == '"')
					{
						y = i;
						while ((*token)->str[y] && (*token)->str[y + 1] != '"')
							y++;
						ft_strlcpy_mod(&(*token)->str[i], &(*token)->str[i + 1],
							y - i + 1);
					}
					if ((*token)->str[i] == '$')
					{
						y = i + 1;
						while ((*token)->str[y]
							&& (ft_isalnum((*token)->str[y]) == true
								|| (*token)->str[y] == '_'))
							y++;
						expand = malloc(sizeof(char) * y - i);
						// printf("%d\n", y - i);
						ft_strlcpy(expand, &(*token)->str[i + 1], y - i);
						env_value = ft_getenv(env, expand);
						// printf("%s\n", expand);
						// printf("%ld\n", ft_strlen((*token)->str) - (y - i)
							+ ft_strlen(env_value) + 1);
						(*token)->str = ft_realloc((*token)->str,
								ft_strlen((*token)->str) - (y - i)
								+ ft_strlen(env_value) + 1);
						while ((*token)->str[y] && ((*token)->str[y] == ' '
								|| (*token)->str[y] == '\t'))
							y++;
						ft_strlcpy(&(*token)->str[ft_strlen(env_value)],
							&(*token)->str[y], ft_strlen(&(*token)->str[y]));
						ft_strlcpy_mod(&(*token)->str[i], env_value,
							ft_strlen(env_value) + 1);
					}
				}
				i++;
			}
		}
		*token = (*token)->next;
	}
	(*token) = head;
}

// probleme avec la chaine apres l'expand (manque un espace et la chaine n'est pas complete).
// retier les single quote
// ''"$PWD"'' ??
// si la variable d'env n'existe pas ne revoie rien

//		Exemple :

// echo $PWD		-->		/home/.....
// echo '$PWD'		-->		$PWD
// echo "$PWD"		-->		/home/.....
// echo ~			-->		/home/.....
// echo "'$PWD'"	-->		/home/.....
// echo '"$PWD"'	-->		"$PWD"

// echo $PWD+ss		-->		/home/.....+ss

//"$USER" salut

//	thliberssalut
