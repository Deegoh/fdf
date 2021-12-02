/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/11/29 09:01:53 by tpinto-m         ###   ########.fr       */
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

int mouse_hook(int mousecode, t_vars *vars)
{
	(void)vars;
	printf("mouseCode:%d\n", mousecode);
	return (0);
}

void square(t_data img, int x, int y, int size, int color)
{
	int large;

	large = size;
	while (size--)
	{
		my_mlx_pixel_put(&img, size + x, y, color);
		my_mlx_pixel_put(&img, size + x, y + large, color);
		my_mlx_pixel_put(&img, x, size + y, color);
		my_mlx_pixel_put(&img, x + large, size + y, color);
	}
}

void circle(t_data img, int x, int y, int radius, int color)
{
	double xpos;
	double ypos;
	int angle;
	int i;

	i = 0;
	while (i < 360)
	{
		angle = i;
		xpos = radius * cos(angle * M_PI / 180);
		ypos = radius * sin(angle * M_PI / 180);
		my_mlx_pixel_put(&img, x + xpos, y + ypos, color);
		i++;
	}
}

int	main(void)
{
	t_vars  mlx;
	t_data	img;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 200, 200, "Hello fdf!");
	img.img = mlx_new_image(mlx.mlx, 200, 200);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_lenght, &img.endian);
	square(img, 50, 50, 100, 0x00000FF);
	circle(img, 100, 100, 50, 0x0000FF00);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
//	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_hook(mlx.win, 2, 1L<<0, key_hook, &mlx);
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_loop(mlx.mlx);
}
