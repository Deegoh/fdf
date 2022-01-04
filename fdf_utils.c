/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/11 11:16:28 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("p:%p\n", vars->mlx);
	printf("keycode:%d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == 49)
		printf("space\n");
	return (0);
}

int	closewin(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	(void)vars;
//	printf("p:%p\n", vars->mlx);
	printf("mouseCode:%d\n", mousecode);
	printf("x:%d\n", x);
	printf("y:%d\n", y);
	return (0);
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

void	EightWaySymmetricPlot(t_data img, int xc, int yc, int x, int y, int color)
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
	EightWaySymmetricPlot(img, xc, yc, x, y, color);
	while (x <= y)
	{
		if (d <= 0)
			d = d + (4 * x) + 6;
		else
			d = d + (4 * x) - (4 * y--) + 10;
		x = x + 1;
		EightWaySymmetricPlot(img, xc, yc, x, y, color);
	}
}

void	drawline(t_data img, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX = endX - beginX;
	double	deltaY = endY - beginY;
	double	pixelX = beginX;
	double	pixelY = beginY;
	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels; // 1
	deltaY /= pixels; // 0
	while (pixels)
	{
		my_mlx_pixel_put(&img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}
