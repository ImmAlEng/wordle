SRC =	main.c	\
		list.c	\
		string.c	\
		get_next_line_utils.c	\
		get_next_line.c	

OBJ = $(SRC:.c=.o)

NAME = wordle

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf  $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re