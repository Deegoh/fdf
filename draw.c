/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/15 19:15:00 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data img, int bx, int by, int endX, int endY, int color)
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
	while (pixels)
	{
		my_mlx_pixel_put(&img, (int)pixelx, (int)pixely, color);
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