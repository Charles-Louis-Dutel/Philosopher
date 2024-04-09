NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

############################Sources########################
SRCS_DIR = philo/
FILES = philo.c \

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

###########################Objects#########################
OBJS = ${SRCS:.c=.o}
# OBJS_ALL = ${OBJS} ${OBJS_BUILTIN}

##########################Libs#############################


##########################Rules############################

all: ${NAME}

${NAME}: ${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
