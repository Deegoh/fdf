CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = fdf
SRC = fdf.c\
	  read_map.c\
	  sort_map.c\
	  error.c\
	  set_hook.c\
	  draw.c\
	  draw_bonus.c
OBJ = $(SRC:.c=.o)

MAP_DIR = test_maps/

MINILIBX_DIR = ./minilibx_macos/

LIBFT_DIR = ./libft/

INCLUDES = -I$(MINILIBX_DIR) -I$(LIBFT_DIR)

FRAMEWORK = -framework OpenGL -framework AppKit

LIB = -lmlx -lm -lft -L $(MINILIBX_DIR) -L $(LIBFT_DIR)

all: $(NAME)

$(NAME): libx libft $(OBJ)
	$(CC) $(LIB) $(INCLUDES) $(FRAMEWORK) $(OBJ) -o $(NAME)
exec: all
	#./$(NAME) test_maps/10-2.fdf
	./$(NAME) test_maps/42.fdf
libx:
	@$(MAKE) -sC $(MINILIBX_DIR)
libft:
	@$(MAKE) -sC $(LIBFT_DIR)
clean:
	rm -rf $(OBJ)
	@$(MAKE) -sC $(MINILIBX_DIR) clean
	@$(MAKE) -sC $(LIBFT_DIR) clean
fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re compile libft minilibx
