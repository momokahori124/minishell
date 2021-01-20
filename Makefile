# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 01:57:04 by tjinichi          #+#    #+#              #
#    Updated: 2021/01/20 19:36:46 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc

CFLAGS = -g                  -fsanitize=address

SRCFILE =	minishell.c \
			minishell_utils.c \
			error.c \
			treat_command_line.c \
			cute_message.c \
			signal.c \
			pwd_command.c \
			exit.c \
			redirect.c \
			pipe.c \
			command_format_check.c \
			is_output_format_error.c \
			is_pipe_format_error.c \
			is_semicolon_format_error.c \
			command_utils_1.c \
			command_utils_2.c \
			command_utils_3.c \
			exec_command.c \
			pipe_redirect_utils.c \
			is_what.c \
			is_what2.c \
			wait_quotation.c \
			read_command_line.c \

SRCDIR = srcs
OBJDIR = $(SRCDIR)/objs

SRCS = $(addprefix $(SRCDIR)/, $(SRCFILE))
OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

LIBS = ./utils/Libft/
LIBFT = ./utils/Libft/libft.a

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(LIBFT)

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
	$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS) $(LIBFT)
	./minishell

valgrind: $(LIBFT) $(OBJS)
	gcc -g -o $(NAME) $(OBJS) $(LIBFT)
	valgrind ./minishell

.PHONY: all clean fclean re FORCE leak
