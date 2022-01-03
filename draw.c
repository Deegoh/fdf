/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/01/03 06:42:33 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->adr + (y * data->line_len + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_line2(t_data d, t_point b, t_point e, int color)
{
	double	deltax;
	double	deltay;
	double	pixelx;
	double	pixely;
	int		pixels;

	deltax = e.x - b.x;
	deltay = e.y - b.y;
	pixelx = b.x;
	pixely = b.y;
	pixels = (int)sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	while (pixels + 1)
	{
		my_mlx_pixel_put(&d, (int)pixelx, (int)pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	draw_wire2(t_data *data)
{
	int		i;
	int		j;
	int		s;
	int		x;
	int		y;

	j = -1;
	s = data->scale;
	while (++j < data->ylen)
	{
		i = 0;
		while (i < data->xlen - 1)
		{
			x = i;
			y = j;
			if (!data->wire[j][i++])
			{
				// i, i+1
				// j, j+1
				draw_line(*data, x, y, x + 1, y, 0x00FFFFFF);
				draw_line(*data, x, y, x, y + 1, 0x00FFFFFF);
//				draw_line(*data, x, y, x + s, y, 0x00FFFFFF);
//				draw_line(*data, x, y, x, y + s, 0x00FFFFFF);
			}
		}
	}
}

//old method to draw line
void	draw_line(t_data d, int bx, int by, int ex, int ey, int color)
{
	double	deltax;
	double	deltay;
	double	pixelx;
	double	pixely;
	int		pixels;

	deltax = ex - bx;
	deltay = ey - by;
	pixelx = bx;
	pixely = by;
	pixels = (int)sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	while (pixels)
	{
		my_mlx_pixel_put(&d, (int)pixelx, (int)pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

//old method to draw
void	draw_wire(t_data *data)
{
	int		i;
	int		j;
	int		s;
	int		x;
	int		y;

	j = -1;
	s = data->scale;
	while (++j < data->ylen)
	{
		i = 0;
		while (i < data->xlen)
		{
			x = i * s;
			y = j * s;
			if (!data->wire[j][i++])
			{
				draw_line(*data, x, y, x + s, y, 0x00FFFFFF);
				draw_line(*data, x, y, x, y + s, 0x00FFFFFF);
				draw_line(*data, x + s, y, x + s, y + s, 0x00FFFFFF);
				draw_line(*data, x, y + s, x + s, y + s, 0x00FFFFFF);
			}
		}
	}
}
