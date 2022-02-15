/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:56:17 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/15 15:12:30 by tpinto-m         ###   ########.fr       */
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

# define SCALE 50
# define Z 4

typedef struct s_data {
	void	*img;
	char	*adr;
	int		bits;
	int		line_len;
	int		endian;
	int		x;
	int		y;
	char	*map;
	int		**wire;
	int		xlen;
	int		ylen;
	int		zmin;
	int		zmax;
	int		xmax;
	int		ymax;
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
	int	color;
}				t_point;

int		ft_nbrlen(int nbr);
int		get_value_map(const char *tmp, int *i);
int		check_z(int value, t_data *d);
void	process_map(t_data *d);

void	set_hooks(t_vars *vars);

void	read_map(char *file, t_data *d);
int		check_xlen(int *xlen);

void	init_win(t_data *img, int size_x, int size_y, int scale);
void	set_ylen(t_data *d);
void	set_xlen(t_data *d);
void	search_values(t_data *data);

int		set_min_value(int x, int px);
int		set_max_value(int x, int px);
int		ft_abs(int value);
void	display_err(const char *str);
int		close_win(t_vars *vars);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line(t_data d, t_point b, t_point e, int color);
void	iso(t_point	*p, int offset);
t_point	create_point(int x, int y, int z);
void	draw_wire(t_data *data);

#endif
