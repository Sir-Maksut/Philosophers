NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror #-pthread -fsanitize=thread -g
SRC = check_arg.c init_data.c philo.c \
	start.c utils_2.c utils.c one_philo.c
SRC_OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): $(SRC_OBJ)
	$(CC) $(CFLAGS) $(SRC_OBJ) -o $(NAME)

clean:
	rm -rf $(SRC_OBJ)

fclean:
	rm -rf $(SRC_OBJ) $(NAME)

re: fclean all

.PHONY: all clean fclean re
