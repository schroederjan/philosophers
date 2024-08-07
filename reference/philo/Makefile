R=\033[1;31m
G=\033[1;32m
RST=\033[0m

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 
#-fsanitize=thread -g
#detect threading issues during runtime

LIB = philo.h
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(G)$(OBJ) was created$(RST)"
	@echo "$(G)$(NAME) was created$(RST)"

clean:
	rm -f $(OBJ)
	@echo "$(R)$(OBJ) was deleted$(RST)"

fclean: clean
	rm -f $(NAME)
	@echo "$(R)$(NAME) was deleted$(RST)"

re: fclean all

.PHONY: all clean fclean re

