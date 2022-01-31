/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/01/31 17:47:19 by tpinto-m         ###   ########.fr       */
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

void	comment(t_data d)
{
	int	j;
	int	i;

	printf("map:\n%s", d.map);
	printf("xlen:%d\n", d.xlen);
	printf("ylen:%d\n", d.ylen);
	printf("zmin:%d\n", d.zmin);
	printf("zmax:%d\n", d.zmax);
	printf("wire:\n");
	i = -1;
	while (++i < d.ylen)
	{
		j = 0;
		while (j < d.xlen)
		{
			printf("%d ", d.wire[i][j++]);
			if (d.wire[i][j] == 0)
				printf(" ");
		}
		printf("\n");
	}
}

int	ft_abs(int value)
{
	if (value < 0)
		return (value * -1);
	return (value);
}

int	main(int ac, char *av[])
{
	t_vars	mlx;
	t_data	d;

	if (ac == 2)
	{
		d.map = ft_strdup("");
		read_map(av[1], &d);
		get_ylen(&d);
		get_xlen(av[1], &d);
		process_map(&d);
		comment(d);
		mlx.mlx = mlx_init();
		init_win(&d, d.xlen, d.ylen, 50);
		mlx.win = mlx_new_window(mlx.mlx, d.x, d.y, "Hello fdf!");
		d.img = mlx_new_image(mlx.mlx, d.x, d.y);
		d.adr = mlx_get_data_addr(d.img, &d.bits, &d.line_len, &d.endian);
//		draw_wire2(&d);
		draw_wire(&d);
		set_hooks(&mlx);
//		mlx_put_image_to_window(mlx.mlx, mlx.win, d.img, 0, ((d.y - (d.ylen + 1) * d.scale) / 2));
		mlx_put_image_to_window(mlx.mlx, mlx.win, d.img, 25, 25);
		mlx_loop(mlx.mlx);
	}
	perror("Missing file");
	return (EXIT_FAILURE);
}
