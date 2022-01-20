NAME 		= so_long
CC 			= cc
FLAGS 		= -Wall -Wextra -Werror
INCLUDE 	= -lmlx -framework OpenGL -framework AppKit
PATH 		= ./src/
PATH_BONUS 	= ./src/bonus/
SRC 		= ft_itoa.c ft_split.c lst_funcs.c so_long.c str_funcs.c clearing.c\
win_creation.c map_validation.c put_images.c enemy_patrols.c parser.c \
plr_moves.c str_funcs2.c

BONUS_SRC 	= ft_itoa_bonus.c ft_split_bonus.c lst_funcs_bonus.c \
so_long_bonus.c str_funcs_bonus.c clearing_bonus.c win_creation_bonus.c \
map_validation_bonus.c put_images_bonus.c enemy_patrols_bonus.c parser_bonus.c \
plr_moves_bonus.c str_funcs2_bonus.c
OBJ 		= $(addprefix $(PATH), $(SRC:.c=.o))
BONUS_OBJ 	= $(addprefix $(PATH), $(BONUS_SRC:.c=.o))

override TMP_OBJ ?= $(OBJ)

$(NAME) : $(TMP_OBJ)
	$(CC) $(FLAGS) $(TMP_OBJ) $(INCLUDE) -o $@

all: $(NAME)

%.o : $(PATH)%.c so_long.h so_long_bonus.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

bonus: 
	TMP_OBJ="$(BONUS_OBJ)"
	make $(NAME)

clean:
	rm -f $(TMP_OBJ)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus