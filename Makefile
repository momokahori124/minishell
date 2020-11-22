NAME = minishell
SRCS = srcs/minishell.c
SRCDIR = srcs/
# SRCS = ${addprefix ${SRCDIR}, ${SRCFILE}}
OBJS = ${SRCS:.c=.o}
CC = gcc
# CFLAGS = -Wall -Werror -Wextra

NAME: ${OBJS}
	${CC} -o ${NAME} ${OBJS}
	# ${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re 


