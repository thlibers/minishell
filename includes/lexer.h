/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:55:58 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/03 17:32:50 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_data_type
{
	T_NULL = 0,
	T_WORD = 1,
	T_RED_IN = 2,
	T_RED_IN_APP,
	T_RED_OUT,
	T_RED_OUT_APP,
	T_PIPE,
	T_AND,
	T_OR
}						t_data_type;

typedef struct s_tok
{
	t_data_type	  type;
	struct s_tok *next;
} t_tok;

typedef struct s_command
{
	char				*command;
	char				**arguments;
	int					arg_count;
}						t_command;

typedef struct s_token
{
	t_command			*comm_args;
	enum e_data_type	type;
	struct s_token		*next;
}						t_token;

// split_tokens.c

char					**ft_splitnoquote(char *s, char c);
void					clear_token(t_token **head);
void	is_inquote(int *quote_state, char c);


#endif
