# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/23 01:57:04 by tjinichi          #+#    #+#              #
#    Updated: 2021/01/25 01:06:45 by tjinichi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra             #    -fsanitize=address
# CFLAGS = -g     -fsanitize=address

SRCFILE =	minishell.c \
			minishell_utils.c \
			error.c \
			treat_command_line.c \
			cute_message.c \
			signal.c \
			update_env.c \
			redirect.c \
			redirect2.c \
			pipe.c \
			command_format_check.c \
			is_output_format_error.c \
			is_pipe_format_error.c \
			is_semicolon_format_error.c \
			command_utils_1.c \
			command_utils_2.c \
			command_utils_3.c \
			command_utils_4.c \
			exec_command.c \
			pipe_redirect_utils.c \
			is_what.c \
			is_what2.c \
			wait_quotation.c \
			read_command_line.c \

SRCDIR = ./srcs
OBJDIR = objs

SRCS = \
	$(addprefix $(SRCDIR)/, $(SRCFILE)) \
	$(BUILTIN_SRCS) \

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
#========== builtin function ===================================================
BUILTIN_DIR = $(SRCDIR)/builtin
BUILTIN_SRCS = $(addprefix $(BUILTIN_DIR)/, \
				utils/is_symbolic_link.c \
				utils/trace_symbolic_src.c \
				bin.c \
				cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c \
)
$(OBJDIR)/%.o : $(BUILTIN_DIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW) Compiling $(RESET)$(UNDER_LINE)"$<"$(RESET)"
#===============================================================================
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

# =========== COLOR ============================================================
RESET		= \033[0m
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENT		= \033[0;35m
CYAAN		= \033[0;36m
WHITE		= \033[0;37m
B_RESET		= \033[0;49m
B_YELLOW	= \033[0;43m
B_CYAAN		= \033[0;46m
BOLD		= \033[1m
UNDER_LINE	= \033[0;4m
