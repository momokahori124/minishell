# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momoka <momoka@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/23 15:04:22 by tjinichi          #+#    #+#              #
#    Updated: 2020/11/23 13:37:06 by momoka           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libvec.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRCS =	add_vec.c \
		crossproduct.c \
		distance_vec.c \
		dotproduct.c \
		intersect_point.c \
		length_vec.c \
		new_vec.c \
		normalize_vec.c \
		scal_times_vec.c \
		substruct_vec.c \
		cos_vec.c \
		scal_sub_vec.c \

OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

all:	$(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re bonus
