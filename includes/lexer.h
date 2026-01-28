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

#include "minishell.h"

enum				e_data_type
{
	T_COMM = 0,
	T_ARG = 1,
	T_RED_IN,
	T_RED_IN_APP,
	T_RED_OUT,
	T_RED_OUT_APP,
	T_PIPE,
	T_HEREDOC
};

typedef struct s_command
{
	char				*command;
	char				**arguments;
}						t_command;

typedef struct s_token
{
	t_command			command;
	enum e_data_type	type;
	struct s_token		*token_next;
}						t_token;

// split_readline.c

char					**ft_splitnoquote(char *s, char c);
