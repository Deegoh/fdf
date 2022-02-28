/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:56:17 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/28 11:54:10 by tpinto-m         ###   ########.fr       */
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

# define Q 12
# define W 13
# define E 14
# define S 1
# define A 0
# define D 2
# define R 15
# define F 3
# define ESC 53
# define SPACE 49
# define U 32
# define O 31
# define I 34
# define K 40
# define J 38
# define L 37
# define P 35

# define SCALE 20
# define Z 12

enum e_proj{isom, cart};

typedef struct s_map {
	int		x;
	int		y;
	char	*map;
	int		**wire;
	int		xlen;
	int		ylen;
	int		xmin;
	int		xmax;
	int		ymax;
	int		zmin;
	int		zmax;
}				t_map;

typedef struct s_cam
{
	int		view;
	double	beta;
	double	gamma;
	double	alpha;
	int		x;
	int		y;
	int		z;
	int		xoffset;
	int		yoffset;
	int		isoxoffset;
	int		isoyoffset;
	int		scale;
}	t_cam;

typedef struct s_fdf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_map				map;
	t_cam				cam;
}						t_fdf;

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct s_coor
{
	t_point	b;
	t_point	e;
}	t_coor;

int		ft_nbrlen(int nbr);
int		get_value_map(const char *tmp, int *i);
int		check_z(int value, t_fdf *fdf);
void	process_map(t_fdf *fdf);

void	move(int keycode, t_fdf *fdf);
void	scale(int keycode, t_fdf *fdf);
void	reset(int keycode, t_fdf *fdf);
void	rot(int keycode, t_fdf *fdf);
int		key_hook(int keycode, t_fdf *fdf);
void	set_hooks(t_fdf *fdf);

void	read_map(char *file, t_fdf *fdf);
int		check_xlen(int *xlen);

void	init_struct(t_fdf *fdf);
void	init_win(t_fdf *fdf, char *str);
void	set_ylen(t_fdf *fdf);
void	set_xlen(t_fdf *fdf);
void	search_values(t_fdf *fdf);

int		ft_min(int value1, int value2);
int		ft_max(int value1, int value2);
int		ft_abs(int value);
void	display_err(const char *str);
int		close_win(t_fdf *fdf);

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
void	draw_line(t_fdf *fdf, t_point b, t_point e, int color);
void	draw_wire(t_fdf *fdf, int color);
void	finish_draw(t_fdf *fdf, int color);

t_point	create_point(int x, int y, int z, t_fdf *fdf);
void	iso(t_point	*p, int xoffset, int yoffset, int view);
void	isocoor(t_fdf *fdf, t_coor	*pts);

void	rotate_x(int *y, int *z, double alpha);
void	rotate_y(int *x, int *z, double beta);
void	rotate_z(int *x, int *y, double gamma);
void	rot_all(t_fdf *fdf, t_coor	*pts);

#endif
