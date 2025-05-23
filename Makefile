NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Wextra -g3

HEAD = include/philo.h
SRC_DIR = src/
OBJ_DIR = objs/

SRC_FILES =	main.c \
			minilib.c \
			parse.c	\
			init.c	\
			eat.c	\
			routine.c	\
			utils.c	\
			ato.c	\

OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(HEAD)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I include -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "It's cleaned !"

fclean: clean
		rm -f $(NAME)
		@echo "It's all cleaned !"

re: fclean all

.PHONY: all clean fclean re
