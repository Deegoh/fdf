/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/29 01:00:13 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_win(t_data *img, int size_x, int size_y, int scale)
{
	img->x = (size_x + 1) * scale * 1;
	img->y = (size_y + 2) * scale * 1;
	img->scale = scale;
}

int	main(int ac, char *av[])
{
	t_vars	mlx;
	t_data	d;

	if (ac == 2)
	{
		d.map = ft_strdup("");
		d.ylen = read_map(av[1], &d);
		process_map(&d);
	}
	printf("map:\n%s", d.map);
//	printf("ylen:%d\n", d.ylen);
//	printf("xlen:%d\n", d.xlen);
	printf("wire:\n");
	int j;
	for (int i = 0; i < d.ylen; ++i)
	{
		j = 0;
		while (j < d.xlen)
		{
			printf("%d", d.wire[i][j++]);
		}
		printf("\n");
	}
	mlx.mlx = mlx_init();
	init_win(&d, d.xlen, d.ylen, 50);
	mlx.win = mlx_new_window(mlx.mlx, d.x, d.y, "Hello fdf!");
	d.img = mlx_new_image(mlx.mlx, d.x, d.y);
	d.adr = mlx_get_data_addr(d.img, &d.bits, &d.line_len, &d.endian);
	draw_map_cart(&d);
//	circle2(d, 250, 250, 200, 0x00571666);
//	draw_line(d, 50, 50, 100, 100, 0x00FFFFFF);
//	draw_line(d, 10, 10, 100, 500, 0x00FFFFFF);
//	circle1(d, 250, 250, 200, 0x00065ccc);
//	square(d, 50, 50, 100, 150, 0x00FFFFFF);
	set_hooks(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, d.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
