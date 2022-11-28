NAME = 		philo

SRC =		philo.c \
			utils.c

HEADER =	philo.h

CC =		cc

CFLAGS =	-Wall -Wextra -Werror -pthread

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
