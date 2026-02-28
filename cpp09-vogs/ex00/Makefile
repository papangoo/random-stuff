NAME = btc

SRCS = BitcoinExchange.cpp main.cpp

HDR = BitcoinExchange.hpp

OBJS = $(SRCS:.cpp=.o)

CPP = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

%.o : %.cpp $(HDR)
	$(CPP) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $(NAME)

.PHONY : all clean fclean re debug

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
