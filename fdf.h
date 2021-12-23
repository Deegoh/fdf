#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"

typedef struct s_data {
	void	*img;
	char	*adr;
	int		bits;
	int		line_len;
	int		endian;
	int		x;
	int		y;
	int		scale;
	char	*map;
	int		line;
}				t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	read_map(char *file, t_data *d);
int	count_line(const char *tmp);
void	process_map(t_data *d);
int	close_win(t_vars *vars);

void	set_hooks(t_vars *vars);

void	draw_line(t_data img, int bx, int by, int endX, int endY, int color);
void	square(t_data img, int posX, int posY, int x, int y, int color);
void	circle1(t_data img, int xc, int yc, int r, int color);
void	circle2(t_data img, int xc, int yc, int radius, int color);
void	eight_way_plot(t_data img, int xc, int yc, int x, int y, int color);

#endif
