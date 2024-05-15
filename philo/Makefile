NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread

SRC = main.c parsing.c utils.c init.c \

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all
