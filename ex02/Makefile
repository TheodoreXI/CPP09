SRCS = PmergeMe.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = PmergeMe
CC = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.cpp PmergeMe.hpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean 
	rm -rf $(NAME)

re: fclean all