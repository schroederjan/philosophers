NAME = philo

COLOR_RED = \033[1;31m
COLOR_GREEN = \033[1;32m
COLOR_RESET = \033[0m

CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -fsanitize=undefined -g

SRCDIR = src
OBJDIR = obj

SRCS = $(shell find $(SRCDIR) -name '*.c')
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo -e "$(COLOR_GREEN)$(notdir $@) was created$(COLOR_RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo -e "$(COLOR_GREEN)All objects were created$(COLOR_RESET)"
	@echo -e "$(COLOR_GREEN)$(NAME) was created$(COLOR_RESET)"

clean:
	rm -f $(OBJDIR)/*.o
	@echo -e "$(COLOR_RED)$(OBJDIR)/*.o files were deleted$(COLOR_RESET)"

fclean: clean
	rm -f $(NAME)
	@echo -e "$(COLOR_RED)$(NAME) was deleted$(COLOR_RESET)"

re: fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader ./src

val:
	@valgrind ./philo 2 300 200 100

.PHONY: all clean fclean re norm val
