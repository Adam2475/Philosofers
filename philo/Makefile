NAME = philo

CC = cc

CFLAGS = -pthread -Wall -Wextra -Werror -g

SRC = main.c parsing.c utils.c init.c \
		utils2.c actions.c case_one.c utils3.c \

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
