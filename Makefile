NAME = so_long
CC = cc
FLAGS = -Wall -Wextra -Werror
SRC = ft_itoa.c ft_split.c lst_funcs.c so_long.c str_funcs.c clearing.c \
win_creation.c map_validation.c put_images.c enemy_patrols.c parser.c \
plr_moves.c str_funcs2.c
OBJ = $(SRC:.c=.o)
INCLUDE = -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(OBJ)
	$(CC) -fsanitize=address -g $(FLAGS) $(OBJ) $(INCLUDE) -o $@

all: $(NAME)

%.o : %.c so_long.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus