/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nclavel <nclavel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:25:31 by nclavel           #+#    #+#             */
/*   Updated: 2026/03/16 14:07:31 by nclavel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "includes/structure.h"

/* ======================= BULTINS ======================= */
/* ----- ft_cd_utils.c ----- */
int		dot_count(char *str);
int		dot_skip(char *new_pwd, int i);
char	*parsing_dir(t_minishell *minishell, char *dir);

/* ----- ft_cd.c ----- */
int		ft_cd(t_minishell *minishell, t_exec *exec, int child_number);

/* ----- ft_echo.c ----- */
int		ft_echo(t_minishell *minishell, t_exec *exec, int child_number);

/* ----- ft_env.c ----- */
int		ft_env(t_minishell *minishell, int child_number);

/* ----- ft_exit.c ----- */
void	ft_exit(t_minishell *minishell, t_exec *exec, int child_number);

/* ----- ft_export_utils.c ----- */
bool	check_env_name(t_minishell *minishell, char **tab, int *i);
char	**add_to_envvalue(t_minishell *minishell, t_exec *exec, int pos);

/* ----- ft_export.c ----- */
void	ft_export(t_minishell *minishell, t_exec *exec, int child_number,
			bool pipe);

/* ----- ft_pwd.c ----- */
int		ft_pwd(t_minishell *minishell, int child_number);

/* ----- ft_unset.c ----- */
void	ft_unset(t_minishell *minishell, t_exec *exec, int child_number);

/* ======================= EXECUTION ======================= */
/* ----- child/child_process.c ----- */
void	child_process(t_minishell *minishell, int child_number);

/* ----- child/child_save.c ----- */
void	child_save(t_exec *exec, int is_child);

/* ----- child/child_utils.c ----- */
void	clean_pipe_fd(t_exec *exec, int child_number, int is_child);

/* ----- child/child.c ----- */
void	init_child(t_exec *exec, int child_number, int is_child);
void	pipes_close(t_exec *exec);

/* ----- convert/convert_ast.c ----- */
char	**ast_to_arr(t_exec *exec, t_ast **ast);

/* ----- convert/convert_env.c ----- */
char	**convert_env(t_env *env);

/* ----- redirection/heredoc/heredoc_utils.c */
int		heredoc_init(t_exec *exec);
int		terminate_heredoc(t_exec *exec);

/* ----- redirection/heredoc/heredoc.c */
int		here_doc(t_exec *exec, t_minishell *minishell);

/* ----- redirection/chose_redirection.c */
bool	redirection_choser(t_exec *exec, t_ast *ast);

/* ----- redirection/open_redirection.c */
int		open_infile(char *filename, int trunc, t_child *child, t_files *files);
int		open_outfile(char *filename, int trunc, t_child *child, t_files *files);
bool	file_opener(t_exec *exec, t_ast *ast, int flag, int (*ptr)(char *, int,
				t_child *, t_files *));

/* ----- exec_utils.c ----- */
void	close_file(t_exec *exec, t_ast *curr_branch);

/* ----- execution.c ----- */
void	execution(t_minishell *minishell);

/* ----- find_path.c ----- */
char	*find_command_path(t_minishell *minishell, char *cmd);

/* ----- init_exec.c ----- */
int		init_exec(t_env *env, t_ast *ast, t_exec *exec, t_minishell *minishell);

/* ======================= MINISHELL ======================= */
/* ----- history.c ----- */
int		init_history(t_minishell *minishell);
int		add_to_history(int fd, char *line);

/* ----- minishell.c ----- */
bool	init_minishell(t_minishell *minishell, char **envp);

/* ----- selector_utils.c ----- */
void	reset_save(t_minishell *minishell);

/* ----- selector.c ----- */
bool	selector(t_minishell *minishell, int i);

/* ======================= PARSING ======================= */
/* ----- ast/ast_utils.c ----- */
int		cmd_count(t_ast *ast);
bool	check_pipe(t_ast *ast);

/* ----- ast/ast.c ----- */
t_ast	*create_tree(t_tok *tok, int i);

/* ----- env/env_utils.c ----- */
t_env	*new_env_node(void *name, void *content);
void	*add_env_back(t_env **head, t_env *node);
bool	edit_env(t_env **env, char *name, char *new_val);
void	swap_env_value(t_env **env);
void	*sort_env(t_env **env);

/* ----- env/env_utils2.c ----- */
t_env	*env_cpy(t_env *env);
char	*ft_getenv(t_env *env, char *to_find);

/* ----- env/init_env.c ----- */
char	**env_spliter(char *vars);
t_env	*create_env_var(char *name, char *value, char *equal_loc);
bool	init_env(t_env **env, char **envp);

/* ----- expand/expand_vars.c ----- */
bool	replace_var(t_tok **token, t_env *env, int *i);
void	ft_tilde(t_env *env, t_tok **token, int i);
void	ft_questionmark(t_minishell *minishell, t_tok **token, int i);

/* ----- expand/expand.c ----- */
bool	dollar_treatements(t_minishell *minishell, t_tok **token, int *i);
void	ft_expand(t_minishell *minishell, t_env *env, t_tok **token);

/* ----- expand/remove_quotes.c ----- */
void	remove_quotes(char **str);

/* ----- lexer/check_lexer.c ----- */
int		is_operator(char *word);

/* ----- lexer/check_synthax.c ----- */
bool	check_quote(t_tok *tok);
bool	check_ope(t_tok *tok);

/* ----- lexer/tokenizer_linkedlst ----- */
char	*tok_str_save(char *line, t_data_type data_type);
t_tok	*tok_create_back(t_tok **tok, t_data_type data_type, char *line);

/* ----- lexer/tokenizer_edgecase ----- */
t_tok	*back_tofirst(t_tok **tok);

/* ----- lexer/tokenizer.c ----- */
t_tok	*tokenizer(char *line);

/* ----- prompt.c ----- */
bool	prompt(t_minishell *minishell);

/* ----- utils.c ----- */
int		is_inquote(int *quote, char c);

/* ======================= UTILS ======================= */
/* ----- clean.c ----- */
void	ft_clear(t_minishell *minishell);
void	free_ast(t_ast **ast);
void	free_tok(t_tok **tok);
void	child_clear(t_minishell *minishell);
void	clean_all(t_minishell *minishell);
void	clean_keep_cmd(t_minishell *minishell);
void	clean_heredoc(t_minishell *minishell);
void	close_heredoc_fd(t_exec *exec);
void	clean_useless_child(t_minishell *minishell);
void	clear_exec(t_minishell *minishell);
void	close_files_fd(t_exec *exec);
void	ptr_env_clean(t_env **env, char **tab);

/* ----- signal.c ----- */
void	handler_heredoc(void);
void	handler_sigint(int signum);
void	handler_sigint_exec(int signum);
void	init_signal(void);
void	child_signal(void);

// DEBUG
void	print_ast(t_ast *ast);
void	print_tok(t_tok *tok);

// OTHER
void	arg_count(t_exec *exec);
void	ptr_free_tab(char ***arr);
void	cleanup_pipe(t_exec *exec);

#endif
