/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:56:17 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/23 17:12:05 by tpinto-m         ###   ########.fr       */
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
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123

# define SCALE 1
# define Z 5
# define HEIGHT 1080
# define WIDTH 1920

# define RED 0x00FF0018
# define SAFFRON 0x00FFA52C
# define YELLOW 0x00FFFF41
# define AO 0x00008018
# define BLUE 0x000000F9
# define VIOLET 0x0086007D
# define BLACK 0x00000000
# define WHITE 0x00FFFFFF

enum e_proj{isom, cart};

typedef struct s_map {
	int		x;
	int		y;
	char	*map;
	int		***wire;
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
	int		scale;
	int		d_scale;
}	t_cam;

typedef struct s_fdf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits;
	int					line;
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
int		get_value_map(const char *tmp, long *i);
int		check_z(int value, t_fdf *fdf);
void	process_map(t_fdf *fdf);

void	move(int keycode, t_fdf *fdf);
void	scale(int keycode, t_fdf *fdf);
void	reset(int keycode, t_fdf *fdf);
void	rot(int keycode, t_fdf *fdf);
int		key_hook(int keycode, t_fdf *fdf);

void	read_map(char *file, t_fdf *fdf);
int		check_hex(const char	*map);

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

void	put_pixel(t_fdf *fdf, int x, int y, int color);
void	sign_pts(t_point *sign, t_point b, t_point e);
void	put_line(t_fdf *fdf, t_point b, t_point e, int color);
void	put_wire(t_fdf *fdf);
void	put_lastwire(t_fdf *fdf);

t_point	new_pts(int x, int y, int z, t_fdf *fdf);
void	iso(t_point	*p, int xoffset, int yoffset, int view);
void	isocoor(t_fdf *fdf, t_coor	*pts);
void	view(int keycode, t_fdf *fdf);

void	rotate_x(int *y, int *z, double alpha);
void	rotate_y(int *x, int *z, double beta);
void	rotate_z(int *x, int *y, double gamma);
void	rot_all(t_fdf *fdf, t_coor	*pts);

double	ft_percent(int start, int end, int current);
int		get_default_color(int z, t_fdf *fdf);

void	rm_wire(t_fdf *fdf);
void	rm_finish_wire(t_fdf *fdf);
void	rm_one_line(t_fdf *fdf);

void	put_one_line(t_fdf *fdf);

char	*mlx_addr(void *img_ptr, int *bits, int *size, int *endian);

#endif
