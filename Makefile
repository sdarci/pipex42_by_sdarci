SRCS		= main.c utils.c parse.c split.c

OBJS		= ${SRCS:.c=.o}

HEAD		= pipex.h

NAME		= pipex

CC			= cc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:	%.c ${HEAD}
		${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
