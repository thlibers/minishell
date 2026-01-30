/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:44 by nclavel           #+#    #+#             */
/*   Updated: 2026/01/30 10:44:36 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Define pour les fonction de signal.h
# define _XOPEN_SOURCE 700
# define MSH_HIST "msh_history"

# include "lexer.h"
# include "color.h"
# include "mylibft/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Vars global pour les signaux
//volatile sig_atomic_t msh_sig = 0;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			equal;
	struct s_env	*next;
}					t_env;

typedef struct s_minishell
{
	t_env			*env;
	t_token			*token;
	int				fd_history;
	int				exit_code;
}					t_minishell;

int					env(t_minishell minishell);

/* ============= BULTIN ============= */

// ft_selector.c
void				selector(t_minishell *minishell);

// ft_cd.c

// ft_echo.c

// ft_env.c
int					ft_env(t_minishell *minishell);

// ft_exit.c
void				ft_exit(t_minishell *minishell, t_command *command);

// ft_export.c
void				ft_export(t_minishell *minishell, t_command *command);
int					ft_export_arg(t_minishell *minishell, t_command *command);
void				ft_export_noarg(t_minishell *minishell);

// ft_pwd.c

// ft_unset.c

/* ============= MINISHELL ============= */

bool				init_minishell(t_minishell *minishell, char **envp);
void				init_signal(void);

/* ============= PARSING ============= */
// env_vars.c
char				**env_spliter(char *vars);
bool				init_env(t_env **env, char **envp);
char				*ft_getenv(t_env *env, char *to_find);

// prompt.c
bool				prompt(t_minishell minishell);

// lexer.c
t_token				*lexer(t_minishell *minishell, char *line);

// tokenizer.c
void  *tokenize(char *line);

/* ============= UTILS ============= */
// check_lexer.c
int				is_operator(char *word);

// clean .c
void				ft_clear(t_minishell *minishell);
void				env_clean(t_env *env, char **tab);
void				free_tab(char **s);

// env_utils.c
t_env				*new_env_node(void *name, void *content);
void				*add_env_back(t_env **head, t_env *node);
void				swap_env_value(t_env **env);
void				*sort_env(t_env **env);
t_env				*env_cpy(t_env *env);

// history.c
int					init_history(t_minishell *minishell);
int					add_to_history(int fd, char *line);

#endif
