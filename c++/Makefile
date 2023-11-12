SRC =	main.cpp	\
		functions.cpp

OBJ = $(SRC:.cpp=.o)

NAME = wordle

CXX = c++

CPPFLAGS = -Wall -Wextra -Werror -std=c++11 -g

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf  $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re