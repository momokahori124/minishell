# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 01:57:04 by tjinichi          #+#    #+#              #
#    Updated: 2020/12/12 04:52:50 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCFILE =	minishell.c \
			minishell_utils.c \
			error.c \
			parse_command.c \
			cute_message.c \
			signal.c \

SRCDIR = srcs/

SRCS = $(addprefix $(SRCDIR), $(SRCFILE))

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBS = ./utils/Libft/
LIBFT = ./utils/Libft/libft.a

SHELL=/bin/bash
COUNT = `expr $C '*' 30 / $T`
PRINT_BAR = $(shell export COUNT=$(COUNT); ./a.sh)

$(NAME): $(OBJS) $(LIBFT)
	$(PRINT_BAR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT): FORCE
	@$(MAKE) -C $(LIBS)

all: $(NAME)

clean:
	@make clean -C $(LIBS)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re FORCE
