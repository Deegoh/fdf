/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 02:49:10 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/29 02:49:46 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
