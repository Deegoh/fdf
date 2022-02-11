/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:56:17 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/10 13:02:49 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"

# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53
# define SPACE 49

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
	int		**wire;
	int		xlen;
	int		ylen;
	int		zmin;
	int		zmax;
	int		minminus;
}				t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	s;
	int	color;
}				t_point;

void	read_map(char *file, t_data *d);
void	set_ylen(t_data *d);
void	set_xlen(t_data *d);
void	init_win(t_data *img, int size_x, int size_y, int scale);

int		ft_nbrlen(int nbr);
int		get_value_map(const char *tmp, int *i);
int		check_z(int value, t_data *d);
void	process_map(t_data *d);
int		set_min_minus(int x, int px);
void	search_min_minus(t_data *data);
int		check_xlen(int *xlen);

void	set_hooks(t_vars *vars);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_abs(int value);
void	iso(int *x, int *y, int z);
void	draw_line(t_data d, t_point b, t_point e, int color);
void	draw_wire(t_data *data);

int		close_win(t_vars *vars);

void	square(t_data img, int posX, int posY, int x, int y, int color);
void	circle1(t_data img, int xc, int yc, int r, int color);
void	circle2(t_data img, int xc, int yc, int radius, int color);
void	eight_way_plot(t_data img, int xc, int yc, int x, int y, int color);

#endif
