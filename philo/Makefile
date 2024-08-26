NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -pthread -MMD #-fsanitize=thread

############################Sources########################
SRCS_DIR = srcs/
FILES = philo init manage_errors utils time

SRCS = $(addprefix $(SRCS_DIR), $(FILES))

###########################Objects#########################
OBJS_DIR = objs_and_deps/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

DEPENDENCIES = $(patsubst %.o, %.d, $(OBJS))
##########################Libs#############################


##########################Rules############################
$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus

-include $(DEPENDENCIES)
