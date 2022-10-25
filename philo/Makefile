NAME =		philo

SRC =		philo.c\
			aesthetics.c

CC =		cc

CFLAGS =#	-Wall -Wextra -Werror

RM = 		rm -f

(NAME):		all

all:
			$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
			$(RM) $(NAME)

fclean:
			$(RM) $(NAME)

re: 		fclean all
