# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sumilee <sumilee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/17 18:38:57 by seohyeki          #+#    #+#              #
#    Updated: 2024/03/23 17:42:30 by sumilee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a
LIBFT_DIR = libft
INC_DIR = include
P_SRCS = parse/parse_env_change.c \
		 parse/parse_env_interpret.c \
		 parse/parse_env_parsing.c \
		 parse/parse_token_beautify.c \
		 parse/parse_token_delete_quote.c \
		 parse/parse_token_split.c \
		 parse/parse.c
E_SRCS = builtins/cd.c \
		 builtins/echo.c \
		 builtins/env.c \
		 builtins/exit.c \
		 builtins/export.c \
		 builtins/pwd.c \
		 builtins/unset.c \
		 builtins/check_cmd_option.c \
		 exec/exec_before_heredoc.c \
		 exec/exec_check_file.c \
		 exec/exec_child_process.c \
		 exec/exec_cmd_utils.c \
		 exec/exec_end.c \
		 exec/exec_fd_utils.c \
		 exec/exec_general_cmd.c \
		 exec/exec_heredoc.c \
		 exec/exec_init.c \
		 exec/exec.c \
		 signal.c \
		 main.c
U_SRCS = utils/env_utils.c \
		 utils/exec_utils.c \
		 utils/free.c \
		 utils/ft_itoa_err.c \
		 utils/ft_strdup_err.c \
		 utils/ft_strndup.c \
		 utils/parse_utils.c \
		 utils/utils.c
P_OBJS = $(P_SRCS:.c=.o)
E_OBJS = $(E_SRCS:.c=.o)
U_OBJS = $(U_SRCS:.c=.o)
A_OBJS = $(P_OBJS) $(E_OBJS) $(U_OBJS)
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(A_OBJS)
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) ./
	cc -lreadline $(CFLAGS) $(LIBFT) -o $@ $^

%.o : %.c
	cc -I$(LIBFT_DIR) -I$(INC_DIR) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(A_OBJS)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME) $(LIBFT)

re :
	make fclean
	make all
	
.PHONY : all clean fclean re