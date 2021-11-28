#ifndef  FDF_H
# define FDF_H

# include <stdio.h>
# include "./minilibx_macos/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}				t_data;

#endif
