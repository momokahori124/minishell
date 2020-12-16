# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 01:57:04 by tjinichi          #+#    #+#              #
#    Updated: 2020/12/16 22:44:46 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCFILE =	minishell.c \
			minishell_utils.c \
			error.c \
			treat_command_line.c \
			cute_message.c \
			signal.c \
			pwd_command.c \
			command_utils.c \
			exec_command.c \
			pipe_redirect_utils.c \
			is_what.c \
			is_what2.c \

SRCDIR = srcs/

SRCS = $(addprefix $(SRCDIR), $(SRCFILE))

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

LIBS = ./utils/Libft/
LIBFT = ./utils/Libft/libft.a

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -fsanitize=address -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT): FORCE
	@make -C $(LIBS)

all: $(NAME)

clean:
	@make clean -C $(LIBS)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBS)
	rm -f $(NAME)

re: fclean all

leak: $(LIBFT) $(OBJS)
	gcc -g -o $(NAME) $(OBJS) $(LIBFT)
	./minishell

valgrind: $(LIBFT) $(OBJS)
	gcc -g -o $(NAME) $(OBJS) $(LIBFT)
	valgrind ./minishell

.PHONY: all clean fclean re FORCE leak
