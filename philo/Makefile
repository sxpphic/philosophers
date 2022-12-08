NAME = 		philo

SRC =		philo.c \
			utils.c \
			utils2.c \
			init.c \
			seeker.c \
			routine_funcs.c \

HEADER =	philo.h

CC =		cc

CFLAGS =	-Wall -Wextra -Werror -pthread -g

RM =		rm -rf

$(NAME):		$(SRC)
				$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) *.dSYM

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re
