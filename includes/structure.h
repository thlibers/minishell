/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:28:21 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/12 14:48:25 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include <stdbool.h>
# include <sys/types.h>

// --- EXECUTION PART ---

typedef struct s_child
{
	char			**cmd;
	int				save[2];
	int				infile_fd;
	int				outfile_fd;
	int				argc;
}	t_child;

typedef struct s_exec
{
	t_child			child;
	// char			**cmd;
	char			**env;
	char			*limiter;
	int				*ptr_exit_code;
	int				(*pipe_fd)[2];
	// int				infile_fd;
	int				heredoc_fd[1024];
	int				heredoc_fd_size;
	int				heredoc_done;
	// int				outfile_fd;
	int				index;
	int				cmdc;
	// int				argc;
	// int				save[2];

}					t_exec;

// --- PARSING PART ---
typedef struct s_expand
{
	char			*expanded;
	char			*arg;
	char			*env_value;
	int				*first_char;
	int				last_char;
}					t_expand;

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
}					t_data_type;

typedef struct s_tok
{
	t_data_type		type;
	char			*str;
	struct s_tok	*next;
	struct s_tok	*prev;
}					t_tok;

typedef struct s_ast
{
	t_data_type		type;
	char			*data;
	struct s_ast	*top;
	struct s_ast	*leaf_right;
	struct s_ast	*leaf_left;
}					t_ast;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			equal;
	struct s_env	*next;
}					t_env;

typedef struct s_quotes
{
	int				first;
	int				last;
	int				quote_type;
	int				len;
	int				i;
}					t_quotes;

// --- COMMON ---
typedef struct s_minishell
{
	t_env			*env;
	t_tok			*tok;
	t_ast			*ast;
	t_exec			exec;
	pid_t			*pid;
	int				tty;
	int				fd_history;
	int				exit_code;
}					t_minishell;

#endif
