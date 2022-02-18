/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:56:17 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/18 16:49:50 by tpinto-m         ###   ########.fr       */
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
# define ESC 53
# define SPACE 49

# define SCALE 50
# define Z 12

typedef struct s_map {
	int		x;
	int		y;
	int		z;
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

typedef struct			s_fdf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_map				*map;
}						t_fdf;

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

int		ft_nbrlen(int nbr);
int		get_value_map(const char *tmp, int *i);
int		check_z(int value, t_fdf *fdf);
void	process_map(t_fdf *fdf);

void	set_hooks(t_fdf *fdf);

void	read_map(char *file, t_fdf *fdf);
int		check_xlen(int *xlen);

void	init_win(t_fdf *fdf, int size_x, int size_y, int scale);
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
void	iso(t_point	*p, int offset);
t_point	create_point(int x, int y, int z);
void	draw_wire(t_fdf *fdf);

#endif
