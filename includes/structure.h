/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 11:28:21 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/20 11:28:59 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include <stdbool.h>
# include <sys/types.h>

// --- EXECUTION PART ---
typedef struct s_command
{
	char				*command;
	char				**arguments;
	int					arg_count;
	int					cmd_count;
}						t_command;

typedef struct s_exec
{
	pid_t				*pid;
	t_command			*com_args;
	char				**env;
	char				*limiter;
	int					(*pipe_fd)[2];
	int					infile_fd;
	int					outfile_fd;
	int					index;
	char				**argv;// delete
	int					heredoc;// ?
	int					argc;// delete
	// char		***cmd_args;	// delete
}						t_exec;

// --- PARSING PART ---
typedef struct s_expand
{
	char	*expanded;
	char	*env_value;
	int		i; // A changer pour quelque chose de plus lisible
	int		y; // A changer pour quelque chose de plus lisible
}				t_expand;

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

typedef struct s_env
{
	char				*name;
	char				*value;
	bool				equal;
	struct s_env		*next;
}						t_env;

// --- COMMON ---
typedef struct s_minishell
{
	t_env				*env;
	t_token				*token;
	t_tok				*tok;
	t_ast				*root;
	int					fd_history;
	int					exit_code;
}						t_minishell;

#endif
