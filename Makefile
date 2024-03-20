# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 18:38:57 by seohyeki          #+#    #+#              #
#    Updated: 2024/03/20 10:54:45 by sumilee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a
LIBFT_DIR = libft
P_SRCS = minishell_env_change.c \
		 minishell_env_interpret.c \
		 minishell_env_parsing.c \
		 minishell_free.c \
		 minishell_token_beautify.c \
		 minishell_token_delete_quote.c \
		 minishell_token_split.c \
		 minishell_utils3.c
E_SRCS = builtins/cd.c \
		 builtins/echo.c \
		 builtins/env.c \
		 builtins/exit.c \
		 builtins/export.c \
		 builtins/pwd.c \
		 builtins/unset.c \
		 builtins/check_cmd_option.c \
		 exec_check_file.c \
		 exec_child_process.c \
		 exec_cmd.c \
		 exec_env_utils.c \
		 exec_fd.c \
		 exec_general_cmd.c \
		 exec_heredoc.c \
		 exec_init.c \
		 exec.c \
		 signal.c \
		 ft_itoa_err.c \
		 utils.c \
		 utils2.c \
		 main.c
P_OBJS = $(P_SRCS:.c=.o)
E_OBJS = $(E_SRCS:.c=.o)
A_OBJS = $(P_OBJS) $(E_OBJS)
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(A_OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) ./
	cc -lreadline $(CFLAGS) $(LIBFT) -o $@ $^

%.o : %.c
	cc -I$(LIBFT_DIR) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(A_OBJS)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME) $(LIBFT)

re :
	make fclean
	make all
	
.PHONY : all clean fclean re