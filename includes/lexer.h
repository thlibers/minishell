/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:55:58 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/28 11:26:36 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
#endif

# include "minishell.h"

typedef struct s_token
{
	char				**command;
	enum e_data_type	type;
	struct s_token		*token_next;
}						t_token;

// split_readline.c

char	**ft_splitnoquote(char *s, char c);
