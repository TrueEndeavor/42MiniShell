# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 10:17:33 by lannur-s          #+#    #+#              #
#    Updated: 2024/02/21 15:46:25 by lannur-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIBFTNAME = libft.a

CC = cc
CCFLAGS = -Wall -Werror -Wextra -I./include -g3 #-fsanitize=address

AR = ar
ARFLAGS = -rcs

LIBFT_DIR = ./include/libft_combined

INCLUDES = -I./include -I$(LIBFT_DIR)/include

SRCS =  src/main.c \
		src/utils.c \
		src/dev/dev_utils.c \
		src/error/error_handler.c \
		src/lexer/lexer_core.c \
		src/lexer/lexer_helper1.c \
		src/lexer/lexer_helper2.c \
		src/lexer/lexer_helper3.c \
		src/lexer/lexer_tokenizer.c \
		src/lexer/token.c \
		src/parser/node_constructors.c \
		src/parser/node_printers.c \
		src/exec/run_cmd.c \
		src/exec/exec.c \
		src/parser/parsing_functions.c \
		src/builtins/builtins_checker.c \
		src/builtins/cd.c \
		src/builtins/echo.c \
		src/builtins/env.c \
		src/builtins/exit.c \
		src/builtins/export.c \
		src/builtins/pwd.c \
		src/builtins/unset.c		
#		src/parser/parser.c \
		src/parser/AST.c \
		
OBJS = $(SRCS:%.c=%.o)

$(NAME): $(LIBFT_DIR)/$(LIBFTNAME) $(OBJS)
	$(CC) $(CCFLAGS) $(SRCS) $(LIBFT_DIR)/$(LIBFTNAME) $(INCLUDES) -lreadline -o ${NAME}


$(LIBFT_DIR)/$(LIBFTNAME):
	make -C $(LIBFT_DIR)

%.o: %.c $(HEADERS)
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS) 
	cd $(LIBFT_DIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && make fclean

re: fclean
	make

.PHONY: all clean fclean re
