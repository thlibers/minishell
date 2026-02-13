/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:55:58 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/09 16:02:00 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_data_type
{
	T_NULL = 0,
	T_WORD = 1,
	T_PIPE = 2,
	T_HERE_DOC = 3,
	T_RED_IN,
	T_RED_OUT,
	T_RED_OUT_APP,
	T_AND,
	T_OR
}						t_data_type;

typedef struct s_tok
{
	t_data_type			type;
	char				*str;
	struct s_tok		*next;
	struct s_tok		*prev;
}						t_tok;

typedef struct s_ast
{
	t_data_type			type;
	char				*data;
	char				*file;
	struct s_ast		*top;
	struct s_ast		*leaf_right;
	struct s_ast		*leaf_left;
}						t_ast;

typedef struct s_token
{
	t_command			*comm_args;
	enum e_data_type	type;
	struct s_token		*next;
}						t_token;

// split_tokens.c

char					**ft_splitnoquote(char *s, char c);
void					clear_token(t_token **head);
int						is_inquote(int *quote, char c);
char					*tok_str_save(char *line, t_data_type data_type);
t_tok					*tok_create_back(t_tok **tok, t_data_type data_type,
							char *line);
int						cmd_count(t_ast *ast);

#endif
