/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:25:31 by nclavel           #+#    #+#             */
/*   Updated: 2026/02/27 15:38:28 by thlibers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "includes/structure.h"

/* ======================= BULTINS ======================= */
/* ----- ft_echo.c ----- */
int		ft_echo(t_exec *exec, int child_number);

/* ----- ft_pwd.c ----- */
int		ft_pwd(t_minishell *minishell, t_env *env, int child_number);

/* ----- ft_cd.c ----- */
void	ft_cd(t_minishell *minishell, t_exec *exec, int child_number);

/* ----- ft_env.c ----- */
int		ft_env(t_minishell *minishell, int child_number);

/* ----- ft_exit.c ----- */
void	ft_exit(t_minishell *minishell, t_exec *exec, int child_number);

/* ----- ft_export.c ----- */
void	ft_export(t_minishell *minishell, t_exec *exec, int child_number);

/* ----- ft_unset.c ----- */
void	ft_unset(t_minishell *minishell, t_exec *exec, int child_number);

/* ======================= EXEC ======================= */
/* ----- child.c ----- */
void	init_child(t_exec *exec, int child_number, int is_child);
void	child_process(t_minishell *minishell, int child_number);

/* ----- commands.c ----- */
char	*find_command_path(t_minishell *minishell, char *cmd);

/* ----- convert_env.c ----- */
char	**convert_env(t_env *env);

/* ----- exec_utils.c ----- */
void	cleanup_pipe(t_minishell *minishell, t_exec *exec);

/* ----- execution.c ----- */
void	execution(t_minishell *minishell);

/* ----- heredoc.c ----- */
int		here_doc(t_exec *exec);

/* ----- init_exe.c ----- */
int		init_exec(t_env *env, t_ast *ast, t_exec *exec);

/* ----- convert.c ----- */
char	**ast_to_arr(t_ast **ast);
void	arg_count(t_exec *exec);
void	free_ast_arr(char ***arr);

/* ======================= MINISHELL ======================= */
/* ----- history.c ----- */
int		init_history(t_minishell *minishell);
int		add_to_history(int fd, char *line);

/* ----- minishell.c ----- */
bool	init_minishell(t_minishell *minishell, char **envp);

/* ----- selector.c ----- */
bool	selector(t_minishell *minishell, int i);

/* ======================= PARSING ======================= */
/* ----- AST/AST.c ----- */
t_ast	*create_tree(t_tok *tok, int i);

/* ----- AST/AST_utils.c ----- */
int		cmd_count(t_ast *ast);

/* ----- env/env_vars.c ----- */
char	**env_spliter(char *vars);
bool	init_env(t_env **env, char **envp);
t_env	*create_env_var(char *name, char *value, char *equal_loc);

/* ----- env/env_utils.c ----- */
t_env	*new_env_node(void *name, void *content);
void	*add_env_back(t_env **head, t_env *node);
bool	edit_env(t_env **env, char *name, char *new_val);
void	swap_env_value(t_env **env);
void	*sort_env(t_env **env);

/* ----- env/env_utils2.c ----- */
char	*ft_getenv(t_env *env, char *to_find);
t_env	*env_cpy(t_env *env);

/* ----- expand/expand.c ----- */
void	ft_expand(t_minishell *minishell, t_env *env, t_tok **token);

/* ----- expand/expand_vars.c ----- */
void	ft_tilde(t_env *env, t_tok **token, int i);
void	ft_questionmark(t_minishell *minishell, t_tok **token, int i);
int		get_location_vars_name_end(t_tok **token, int i);
bool	replace_var(t_tok **token, t_env *env, int *i);

/* ----- expand/remove_quotes.c ----- */
void	remove_quotes(char **str);

/* ----- lexer/tokenizer.c ----- */
t_tok	*tokenizer(char *line);

/* ----- lexer/tokenizer_linked_list ----- */
char	*tok_str_save(char *line, t_data_type data_type);
t_tok	*tok_create_back(t_tok **tok, t_data_type data_type, char *line);
void	back_tofirst(t_tok **tok);

/* ----- lexer/check_lexer.c ----- */
int		is_operator(char *word);

/* ----- lexer/check_synthax.c ----- */
bool	check_quote(t_tok *tok);
bool	check_ope(t_tok *tok);

/* ----- prompt.c ----- */
bool	prompt(t_minishell *minishell);

/* ----- utils.c ----- */
int		is_inquote(int *quote, char c);
void	free_tab(char **s);

/* ======================= UTILS ======================= */
/* ----- cd_utils.c ----- */
int		dotcount(char *str);
char	*path_builder(t_env *env, char *dir);

/* ----- clean.c ----- */
void	ft_clear(t_minishell *minishell);
void	env_clean(t_env *env, char **tab);
void	free_ast(t_ast **ast);
void	free_tok(t_tok **tok);
void	child_clear(t_minishell *minishell);

/* ----- signal.c ----- */
void	handler_sigint(int signum);
void	init_signal(void);

// DEBUG
void	print_ast(t_ast *ast);
void	print_tok(t_tok *tok);

#endif
