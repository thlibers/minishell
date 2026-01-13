# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nclavel <nclavel@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/12 11:04:15 by nclavel           #+#    #+#              #
#    Updated: 2026/01/12 11:05:33 by nclavel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME					=	minishell
CC						=	cc
CFLAGS					=	-Wall -Wextra -Werror -lreadline -I.

MINISHELL_FILE			=	$(SRCS_DIR)/clean.c\
							$(SRCS_DIR)/envir_vars.c\
							$(SRCS_DIR)/history.c\
							$(SRCS_DIR)/linked_list_utils.c\
							$(SRCS_DIR)/minishell.c\
							$(SRCS_DIR)/parsing.c\
							$(SRCS_DIR)/prompt.c\
							$(SRCS_DIR)/buildin/env.c\
							$(SRCS_DIR)/buildin/exit.c
SRCS_DIR				=	srcs
OBJS_DIR				=	objs
OBJS					=   $(MINISHELL_FILE:%.c=%.o)

%.o: %.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $^ -o $(NAME) 
