NAME = philo

CC = cc

CFLAGS = -pthread -Wall -Wextra -Werror

SRC = main.c parsing.c utils.c init.c \
		itoa.c actions.c case_one.c \

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
