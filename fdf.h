/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:56:17 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/28 23:41:03 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
	int		**wire;
	int		xlen;
	int		ylen;
}				t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_point {
	int		x;
	int		y;
	int		z;
	int		color;
}				t_point;

int		read_map(char *file, t_data *d);
int		count_line(const char *tmp);
void	process_map(t_data *d);
void	draw_map_cart(t_data *data);
int		close_win(t_vars *vars);

void	set_hooks(t_vars *vars);

void	draw_line(t_data d, int bx, int by, int endX, int endY, int color);
void	square(t_data img, int posX, int posY, int x, int y, int color);
void	circle1(t_data img, int xc, int yc, int r, int color);
void	circle2(t_data img, int xc, int yc, int radius, int color);
void	eight_way_plot(t_data img, int xc, int yc, int x, int y, int color);

#endif
