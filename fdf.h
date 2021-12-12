#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}				t_data;

typedef struct  s_vars {
	void    *mlx;
	void    *win;
	int     x;
	int     y;
	int     inter;
}               t_vars;

int read_map(char *file, char **gnl);

#endif
