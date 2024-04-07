# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lannur-s <lannur-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 10:17:33 by lannur-s          #+#    #+#              #
#    Updated: 2024/04/07 17:33:00 by lannur-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFTNAME = libft.a

CC = cc
CCFLAGS = -Wall -Werror -Wextra -I./include -g #-fsanitize=address

AR = ar
ARFLAGS = -rcs

LIBFT_DIR = ./include/libft_combined

INCLUDES = -I./include -I$(LIBFT_DIR)/include

#src/01minishell_core/create_heredocs.c 

SRCS =  src/main.c \
		src/01minishell_core/handle_heredoc.c \
		src/01minishell_core/prompt_handler.c \
		src/01minishell_core/minishell_compiler.c \
		src/01minishell_core/utils.c \
		src/01minishell_core/utils2.c \
		src/02lexer/lexer_core.c \
		src/02lexer/lexer_parse_word.c \
		src/02lexer/lexer_parse_variable.c \
		src/02lexer/lexer_helper1.c \
		src/02lexer/lexer_helper2.c \
		src/02lexer/lexer_utils.c \
		src/02lexer/lexer_tokenizer.c \
		src/02lexer/token.c \
		src/03parser/expand.c \
		src/03parser/expand_variables.c \
		src/03parser/expand_utils.c \
		src/03parser/node_constructors.c \
		src/03parser/node_constructors2.c \
		src/03parser/node_printers.c \
		src/03parser/parsing_functions.c \
		src/03parser/parsing_helper1.c \
		src/03parser/parsing_helper2.c \
		src/03parser/parsing_helper3.c \
		src/03parser/syntax_analyzer.c \
		src/03parser/transition_functions.c \
		src/03parser/quoting.c \
		src/03parser/quoting_helper.c \
		src/03parser/parsing_utils.c \
		src/04exec/exec.c \
		src/04exec/exec_utils.c \
		src/04exec/run_cmd.c \
		src/04exec/run_cmd_pipe.c \
		src/05builtins/builtins_checker.c \
		src/05builtins/builtins_utils.c \
		src/05builtins/cd.c \
		src/05builtins/echo.c \
		src/05builtins/env.c \
		src/05builtins/exit.c \
		src/05builtins/export.c \
		src/05builtins/pwd.c \
		src/05builtins/unset.c \
		src/05builtins/env/env_conversion.c \
		src/05builtins/env/env_utils.c \
		src/05builtins/env/display_env.c \
		src/05builtins/env/ft_lstclear_env.c \
		src/05builtins/env/ft_lstnew_env.c \
		src/05builtins/env/ft_lstadd_back_env.c \
		src/05builtins/env/ft_lstdelone_env.c \
		src/05builtins/env/ft_lstlast_env.c \
		src/05builtins/env/ft_lstsize_env.c \
		src/05builtins/env/deep_copy_env.c \
		src/05builtins/env/sort_env_list.c \
		src/05builtins/env/get_env.c \
		src/05builtins/env/get_node.c \
		src/05builtins/env/set_env.c \
		src/06signals/process_signals.c \
		src/06signals/signal_setters.c \
		src/06signals/signal_handlers.c \
		src/07error/error_handler.c \
		src/07error/free_handler.c
		
		
OBJS = $(SRCS:%.c=%.o)

$(NAME): $(LIBFT_DIR)/$(LIBFTNAME) $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBFT_DIR)/$(LIBFTNAME) $(INCLUDES) -lreadline -o ${NAME}


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
