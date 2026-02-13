# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thlibers <thlibers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/12 11:04:15 by nclavel           #+#    #+#              #
#    Updated: 2026/02/09 15:58:11 by thlibers         ###   ########.fr        #
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
SRCS = $(SRC_DIR)/builtins/ft_cd.c\
		$(SRC_DIR)/builtins/ft_echo.c\
		$(SRC_DIR)/builtins/ft_env.c\
		$(SRC_DIR)/builtins/ft_exit.c\
		$(SRC_DIR)/builtins/ft_export.c\
		$(SRC_DIR)/builtins/ft_pwd.c\
		$(SRC_DIR)/builtins/ft_unset.c\
		$(SRC_DIR)/minishell/history.c\
		$(SRC_DIR)/minishell/main.c\
		$(SRC_DIR)/minishell/minishell.c\
		$(SRC_DIR)/minishell/selector.c\
		$(SRC_DIR)/parsing/env_vars.c\
		$(SRC_DIR)/parsing/expand.c\
		$(SRC_DIR)/parsing/expand_vars.c\
		$(SRC_DIR)/parsing/prompt.c\
		$(SRC_DIR)/parsing/AST/tokenizer.c\
		$(SRC_DIR)/parsing/AST/tokenizer_linked_list.c\
		$(SRC_DIR)/parsing/check_synthax.c\
		$(SRC_DIR)/parsing/AST/AST.c\
		$(SRC_DIR)/parsing/AST/AST_utils.c\
		$(SRC_DIR)/utils/check_lexer.c\
		$(SRC_DIR)/utils/clean.c\
		$(SRC_DIR)/utils/env_utils.c\
		$(SRC_DIR)/utils/cd_utils.c\
		$(SRC_DIR)/utils/signal.c\
		$(SRC_DIR)/utils/split_tokens.c

# Obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

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
