/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/12 19:23:58 by tpinto-m         ###   ########.fr       */
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
//	printf("p:%p\n", vars->mlx); //segfault
	printf("mouseCode:%d\n", mousecode);
	printf("x:%d\n", x);
	printf("y:%d\n", y);
	return (0);
}

void drawLine(t_data img, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX;
	double deltaY;
	double pixelX;
	double pixelY;
	int pixels;

	deltaX = endX - beginX;
	deltaY = endY - beginY;
	pixelX = beginX;
	pixelY = beginY;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	while (pixels)
	{
		my_mlx_pixel_put(&img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}
void    initWin(t_vars *img, int size_x, int size_y, int inter)
{
	img->x = size_x;
	img->y = size_y;
	img->inter = inter;
}

int main(int ac, char *av[])
{
	t_vars mlx;
	t_data	img;
	char *map;

	map = ft_strdup("");
	if (ac == 2)
		read_map(av[1], &map);
	printf("map:\n%s\n", map);
	mlx.mlx = mlx_init();
	initWin(&mlx, 500,500, 50);
	mlx.win = mlx_new_window(mlx.mlx, mlx.x, mlx.y, "Hello fdf!");
	img.img = mlx_new_image(mlx.mlx, mlx.x, mlx.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_lenght, &img.endian);
	drawLine(img, 0, 0, 500, 500, 0x00FFFFFF);
	mlx_hook(mlx.win, 2, 1L<<0, key_hook, &mlx);
	mlx_hook(mlx.win, 17, 0, closeWin, &mlx);
	mlx_hook(mlx.win, 5, 0, mouse_hook, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
