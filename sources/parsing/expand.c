/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:46:00 by thlibers          #+#    #+#             */
/*   Updated: 2026/02/10 18:21:15 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// void	remove_quotes(char *str)
// {
// 	int		i;
// 	int		len;
// 	int		first_quote;
// 	int		last_quote;
// 	int		quote_type;

// 	i = 0;
// 	first_quote = -1;
// 	last_quote = -1;
// 	quote_type = IN_RESET;
// 	len = ft_strlen(str);
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' && quote_type == IN_RESET)
// 		{
// 			quote_type = IN_SINGLE_QUOTE;
// 			first_quote = i;	
// 		}
// 		else if (str[i] == '"' && quote_type == IN_RESET)
// 		{
// 			quote_type = IN_DOUBLE_QUOTE;
// 			first_quote = i;
// 		}
// 		if ((quote_type == IN_SINGLE_QUOTE && str[i] == '\'') || (quote_type == IN_DOUBLE_QUOTE && str[i] == '\"'))
// 		{
// 			last_quote = i;
// 			ft_memmove(&str[first_quote], &str[first_quote + 1], len - 2);
// 			str[len - 2] = '\0';
// 			str = ft_realloc(str, len - 1);
// 			quote_type = IN_RESET;
// 		}
// 		i++;
// 	}
// }


void	ft_expand(t_env *env, t_tok **token)
{
	int		i;
	int		y;
	int		in_quote;
	char	*expand;
	char	*env_value;
	char	*arg;
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
					while ((*token)->str[i] && is_inquote(&in_quote , (*token)->str[i]) == IN_SINGLE_QUOTE)
						i++;
				}
				else
				{
					if ((*token)->str[i] == '$')
					{
						y = i + 1;
						while ((*token)->str[y] && (ft_isalnum((*token)->str[y]) == true || (*token)->str[y] == '_'))
							y++;
						expand = malloc(sizeof(char) * y - i);
						printf("exp_len = %d\n", y - i);
						ft_strlcpy(expand, &(*token)->str[i + 1], y - i);
						arg = malloc(ft_strlen((*token)->str) - y + 1);
						ft_strlcpy(arg, &(*token)->str[y + 1], ft_strlen((*token)->str) - y);
						env_value = ft_getenv(env, expand);
						printf("expand = %s\n", expand);
						printf("%ld\n", ft_strlen((*token)->str) - (y - i) + ft_strlen(env_value) + 1);
						(*token)->str = ft_realloc((*token)->str, ft_strlen((*token)->str) - (y - i) + ft_strlen(env_value) + 1);
						ft_strlcpy(&(*token)->str[i], env_value, ft_strlen(env_value) + 1);
						(*token)->str = ft_strjoin((*token)->str, arg);				// FREE ANCIEN TOK->STR
						free(arg);
						free(expand);
					}
				}
				i++;
			}
			// remove_quotes(token);
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
// echo "'$PWD'"	-->		'/home/...'
// echo '"$PWD"'	-->		"$PWD"

// echo $PWD+ss		-->		/home/.....+ss
