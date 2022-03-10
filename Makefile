CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
NAME = fdf
SRC = fdf.c\
	  read_map.c\
	  sort_map.c\
	  key_hook.c\
	  draw.c\
	  init_values.c\
	  fdf_utils.c\
	  rot.c\
	  projection.c\
	  color.c\
	  rm.c\
	  mlx.c
OBJ = $(SRC:.c=.o)

MAP_DIR = test_maps/

MINILIBX_DIR = ./minilibx_macos/

LIBFT_DIR = ./libft/

INCLUDES = -I$(MINILIBX_DIR) -I$(LIBFT_DIR)

FRAMEWORK = -framework OpenGL -framework AppKit

LIB = -lmlx -lm -lft -L $(MINILIBX_DIR) -L $(LIBFT_DIR)

all: $(NAME)

$(NAME): libx libft $(OBJ)
	$(CC) $(CFLAGS) $(LIB) $(INCLUDES) $(FRAMEWORK) $(OBJ) -o $(NAME)
exec: clean all
	./$(NAME) test_maps/elem-col.fdf
norm:
	norminette $(SRC)
libx:
	@$(MAKE) -sC $(MINILIBX_DIR)
libft:
	@$(MAKE) -sC $(LIBFT_DIR)
clean:
	rm -rf $(OBJ)
#	@$(MAKE) -sC $(MINILIBX_DIR) clean
#	@$(MAKE) -sC $(LIBFT_DIR) clean
fclean: clean
	rm -rf $(NAME)
	@#$(MAKE) -sC $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re compile libft minilibx
