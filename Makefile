# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momoka <momoka@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 01:57:04 by tjinichi          #+#    #+#              #
#    Updated: 2020/11/23 13:35:29 by momoka           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCFILE = minishell.c

SRCDIR = srcs/

SRCS = $(addprefix $(SRCDIR), $(SRCFILE))

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIBS = ./utils/Libft/
LIBFT = ./utils/Libft/libft.a

$(NAME): $(OBJS)
	@make -C $(LIBS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

all: $(NAME)

clean:
	@make clean -C $(LIBS)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
