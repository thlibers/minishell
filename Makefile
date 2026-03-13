# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/12 11:04:15 by nclavel           #+#    #+#              #
#    Updated: 2026/03/13 16:19:17 by thlibers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME = minishell

# Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I.
INCLUDES = -I./includes

# Paths
SRC_DIR = sources
OBJ_DIR = obj
LIBFT_DIR = mylibft

LIBFT = $(LIBFT_DIR)/libft.a

# Srcs
SRCS =	$(SRC_DIR)/builtins/ft_cd_utils.c\
		$(SRC_DIR)/builtins/ft_cd.c\
		$(SRC_DIR)/builtins/ft_echo.c\
		$(SRC_DIR)/builtins/ft_env.c\
		$(SRC_DIR)/builtins/ft_exit.c\
		$(SRC_DIR)/builtins/ft_export_utils.c\
		$(SRC_DIR)/builtins/ft_export.c\
		$(SRC_DIR)/builtins/ft_pwd.c\
		$(SRC_DIR)/builtins/ft_unset.c\
		$(SRC_DIR)/execution/child/child_process.c\
		$(SRC_DIR)/execution/child/child_save.c\
		$(SRC_DIR)/execution/child/child_utils.c\
		$(SRC_DIR)/execution/child/child.c\
		$(SRC_DIR)/execution/convert/convert_ast.c\
		$(SRC_DIR)/execution/convert/convert_env.c\
		$(SRC_DIR)/execution/redirection/heredoc/heredoc_utils.c\
		$(SRC_DIR)/execution/redirection/heredoc/heredoc.c\
		$(SRC_DIR)/execution/redirection/chose_redirection.c\
		$(SRC_DIR)/execution/redirection/open_redirection.c\
		$(SRC_DIR)/execution/exec_utils.c\
		$(SRC_DIR)/execution/execution.c\
		$(SRC_DIR)/execution/find_path.c\
		$(SRC_DIR)/execution/init_exec.c\
		$(SRC_DIR)/minishell/history.c\
		$(SRC_DIR)/minishell/main.c\
		$(SRC_DIR)/minishell/minishell.c\
		$(SRC_DIR)/minishell/selector_utils.c\
		$(SRC_DIR)/minishell/selector.c\
		$(SRC_DIR)/parsing/ast/ast_utils.c\
		$(SRC_DIR)/parsing/ast/ast.c\
		$(SRC_DIR)/parsing/env/env_utils.c\
		$(SRC_DIR)/parsing/env/env_utils2.c\
		$(SRC_DIR)/parsing/env/init_env.c\
		$(SRC_DIR)/parsing/expand/expand_vars.c\
		$(SRC_DIR)/parsing/expand/expand.c\
		$(SRC_DIR)/parsing/expand/remove_quotes.c\
		$(SRC_DIR)/parsing/lexer/check_lexer.c\
		$(SRC_DIR)/parsing/lexer/check_syntax.c\
		$(SRC_DIR)/parsing/lexer/tokenizer_edgecase.c\
		$(SRC_DIR)/parsing/lexer/tokenizer_linkedlst.c\
		$(SRC_DIR)/parsing/lexer/tokenizer.c\
		$(SRC_DIR)/parsing/prompt.c\
		$(SRC_DIR)/parsing/utils.c\
		$(SRC_DIR)/utils/clean/clean_structure.c\
		$(SRC_DIR)/utils/clean/clean_child.c\
		$(SRC_DIR)/utils/clean/clean.c\
		$(SRC_DIR)/utils/signal.c

# Obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN = \e[0;32m
RED = \e[0;31m
BLUE = \e[0;34m
RESET = \e[0m

all: $(NAME)

# Compilation program
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Compilation files obj
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compilation mylibft
$(LIBFT):
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✓ libft compiled!$(RESET)"

# Clean obj files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

# Complete clean
fclean: clean
	@echo "$(RED)Cleaning executables...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)✓ Full clean completed!$(RESET)"

# Complete recompilation
re: fclean all

# Leaks
valgrind: $(NAME)
	@echo "$(BLUE)Checking for memory leaks with valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

# Rule .PHONY
.PHONY: all clean fclean re test leaks valgrind
