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

int key_hook(int keycode, t_vars *vars)
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

int closeWin(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	(void)vars;
//	printf("p:%p\n", vars->mlx);
	printf("mouseCode:%d\n", mousecode);
	printf("x:%d\n", x);
	printf("y:%d\n", y);
	return (0);
}

void square(t_data img, int posX, int posY, int x, int y, int color)
{
	int large;

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

void circle2(t_data img, int xc, int yc, int radius, int color)
{
	int x;
	int y;

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

void    EightWaySymmetricPlot(t_data img, int xc, int yc, int x, int y, int color)
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

void circle1(t_data img, int xc, int yc, int r, int color)
{
	int x;
	int y;
	int d;

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

void drawLine(t_data img, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	double pixelX = beginX;
	double pixelY = beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

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

int main(void)
{
	t_vars mlx;
	t_data	img;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 500, 500, "Hello fdf!");
	img.img = mlx_new_image(mlx.mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_lenght, &img.endian);
//	circle2(img, 250, 250, 200, 0x00571666);
//	circle1(img, 250, 250, 200, 0x00065ccc);
	square(img, 50, 50, 100, 100, 0x00FFFFFF);
	drawLine(img, 0, 0, 500, 500, 0x00FFFFFF);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_hook(mlx.win, 2, 1L<<0, key_hook, &mlx);
	mlx_hook(mlx.win, 17, 0, closeWin, &mlx);
	mlx_hook(mlx.win, 5, 0, mouse_hook, &mlx);
	mlx_loop(mlx.mlx);
}
