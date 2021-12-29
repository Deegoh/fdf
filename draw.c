/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/29 01:39:15 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->adr + (y * data->line_len + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data data, int bx, int by, int endX, int endY, int color)
{
	double	deltax;
	double	deltay;
	double	pixelx;
	double	pixely;
	int		pixels;

	deltax = endX - bx;
	deltay = endY - by;
	pixelx = bx;
	pixely = by;
	pixels = (int)sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	while (pixels + 1)
	{
		my_mlx_pixel_put(&data, (int)pixelx, (int)pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	square(t_data img, int posX, int posY, int x, int y, int color)
{
	int	large;

	large = x;
	while (large--)
	{
		my_mlx_pixel_put(&img, posX + large, posY, color);
		my_mlx_pixel_put(&img, posX + large, posY + y, color);
	}
	large = y;
	while (large--)
	{
		my_mlx_pixel_put(&img, posX, posY + large, color);
		my_mlx_pixel_put(&img, posX + x, posY + large, color);
	}
}

void	circle2(t_data img, int xc, int yc, int radius, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < 500)
	{
		x = 0;
		while (x < 500)
		{
			if (pow((x - xc), 2) + pow((y - yc), 2) <= (radius * radius))
				my_mlx_pixel_put(&img, x, y, color);
			x++;
		}
		y++;
	}
}

void	eight_way_plot(t_data img, int xc, int yc, int x, int y, int color)
{
	my_mlx_pixel_put(&img, x + xc, -y + yc, color);
	my_mlx_pixel_put(&img, y + xc, -x + yc, color);
	my_mlx_pixel_put(&img, y + xc, x + yc, color);
	my_mlx_pixel_put(&img, x + xc, y + yc, color);
	my_mlx_pixel_put(&img, -x + xc, y + yc, color);
	my_mlx_pixel_put(&img, -y + xc, x + yc, color);
	my_mlx_pixel_put(&img, -y + xc, -x + yc, color);
	my_mlx_pixel_put(&img, -x + xc, -y + yc, color);
}

void	circle1(t_data img, int xc, int yc, int r, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = r;
	d = 3 - (2 * r);
	eight_way_plot(img, xc, yc, x, y, color);
	while (x <= y)
	{
		if (d <= 0)
			d = d + (4 * x) + 6;
		else
			d = d + (4 * x) - (4 * y--) + 10;
		x = x + 1;
		eight_way_plot(img, xc, yc, x, y, color);
	}
}

void	draw_map_cart(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	s;

	j = 0;
	s = data->scale;
	while (j < data->ylen)
	{
		i = 0;
		while (i < data->xlen - 1)
		{
			x = i * s + s;
			y = j * s + s;
			draw_line(*data, x, y, x + s, y, 0x00FFFFFF);
			draw_line(*data, x, y + s, x + s, y + s, 0x00FFFFFF);
			draw_line(*data, x, y, x, y + s, 0x00FFFFFF);
			draw_line(*data, x + s, y, x + s, y + s, 0x00FFFFFF);
			if (data->wire[j][i])
			{
				draw_line( *data, x, y + s, x + s / 2, y + s - data->wire[j][i] * 10, 0x00FFFFFF);
				draw_line( *data, x + s, y + s, x + s / 2, y + s - data->wire[j][i] * 10, 0x00FFFFFF);
				draw_line( *data, x, y, x + s / 2, y + s - data->wire[j][i] * 10, 0x00FFFFFF);
				draw_line( *data, x + s, y, x + s / 2, y + s - data->wire[j][i] * 10, 0x00FFFFFF);
			}
			i++;
		}
		j++;
	}
}
