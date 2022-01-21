NAME 		= so_long
#NAME_BONUS 	= so_long_bonus
CC 			= cc
FLAGS 		= -Wall -Wextra -Werror
INCLUDE 	= -lmlx -framework OpenGL -framework AppKit
PATH 		= ./src/
PATH_BONUS 	= ./src_bonus/
SR		= ft_itoa.c ft_split.c lst_funcs.c so_long.c str_funcs.c clearing.c\
win_creation.c map_validation.c put_images.c enemy_patrols.c parser.c \
plr_moves.c str_funcs2.c
BONUS_SR 	= ft_itoa_bonus.c ft_split_bonus.c lst_funcs_bonus.c \
so_long_bonus.c str_funcs_bonus.c clearing_bonus.c win_creation_bonus.c \
map_validation_bonus.c put_images_bonus.c enemy_patrols_bonus.c parser_bonus.c \
plr_moves_bonus.c str_funcs2_bonus.c
SRC			= $(addprefix $(PATH), $(SR))
BONUS_SRC	= $(addprefix $(PATH_BONUS), $(BONUS_SR))
OBJ 		= $(SRC:.c=.o)
BONUS_OBJ 	= $(BONUS_SRC:.c=.o)
D			= $(SRC:.c=.d)
BONUS_D 	= $(BONUS_SRC:.c=.d)

#override $(TMP_OBJ) ?= (OBJ)

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(FLAGS) $(OBJ) $(INCLUDE) -o $@

%.o : %.c
		$(CC) $(FLAGS) -c $< -o $@ -MD

include 		$(wildcard $(D) $(BONUS_D))

bonus : 
		make OBJ="$(BONUS_OBJ)" all

clean :
	rm -f $(OBJ) $(BONUS_OBJ)
	rm -f $(D) $(BONUS_D)

fclean : clean
		rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus