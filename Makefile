NAME = so_long
CC = gcc -lmlx -framework OpenGL -framework AppKit -Wall -Wextra -Werror
SRC = ft_itoa.c ft_split.c lst_funcs.c so_long.c str_funcs.c clearing.c \
win_creation.c map_validation.c put_images.c enemy_patrols.c parser.c \
plr_moves.c str_funcs2.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ) so_long.h
	CC $(OBJ) -o $(NAME)

%.o : %.c so_long.h Makefile
	CC $(SRC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus