/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/01/03 21:23:53 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_win(t_data *img, int size_x, int size_y, int scale)
{
	img->x = (size_x + 1) * scale * 1;
	img->y = (size_y + 1) * scale * 1.5;
	img->scale = scale;
}

int	close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

void	cart_to_iso(t_point *p);
t_point	iso(t_point p, int i);

int	main(int ac, char *av[])
{
	t_vars	mlx;
	t_data	d;

	if (ac != 2)
	{
		printf("T'es con ou quoi, il manque un fichier");
		exit(0);
	}
	d.map = ft_strdup("");
	read_map(av[1], &d);
	get_ylen(&d);
	get_xlen(av[1], &d);
	process_map(&d);
//	printf("map:\n%s", d.map);
//	printf("xlen:%d\n", d.xlen);
//	printf("ylen:%d\n", d.ylen);
//	printf("zmin:%d\n", d.zmin);
//	printf("zmax:%d\n", d.zmax);
//	printf("\nwire:\n");
//	int j;
//	for (int i = 0; i < d.ylen; ++i)
//	{
//		j = 0;
//		while (j < d.xlen)
//		{
//			printf("%d ", d.wire[i][j++]);
//			if (d.wire[i][j] == 0)
//				printf(" ");
//		}
//		printf("\n");
//	}
	mlx.mlx = mlx_init();
	init_win(&d, d.xlen, d.ylen, 50);
	mlx.win = mlx_new_window(mlx.mlx, d.x, d.y, "Hello fdf!");
	d.img = mlx_new_image(mlx.mlx, d.x, d.y);
	d.adr = mlx_get_data_addr(d.img, &d.bits, &d.line_len, &d.endian);
	draw_wire2(&d);
//	draw_wire(&d);
//	circle2(d, 250, 250, 200, 0x00571666);
//	draw_line2(d, b, e, 0x0000ffff);
//	draw_line(d, 0, 0, 100, 500, 0x00ffffff);
//	circle1(d, 250, 250, 200, 0x00065ccc);
//	square(d, 50, 50, 100, 150, 0x00FFFFFF);
	set_hooks(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, d.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
