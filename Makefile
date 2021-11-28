CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx
NAME = fdf
SRC = fdf.c
OBJ = $(SRC:.c=.o)

MAP_DIR = test_maps/

MINILIBX_DIR = ./minilibx_macos/
MLXFLAGS = -L$(MINILIBX_DIR) -lmlx

INCLUDES = -I$(MINILIBX_DIR)

OPENGL = -framework OpenGL
APPKIT = -framework AppKit

FRAMEWORK = $(OPENGL) $(APPKIT)\

LIB = $(MLXFLAGS)

all: libx $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LIB) $(FRAMEWORK) $(OBJ) -o $(NAME)

libx:
	@$(MAKE) -sC $(MINILIBX_DIR)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re compile
