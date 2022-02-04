/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/04 20:49:49 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_win(t_data *img, int size_x, int size_y, int scale)
{
	img->x = (size_x + 1) * scale * 1.5;
	img->y = (size_y+ 1) * scale * 1.5;
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
	printf("maplen:%d\n", ft_strlen(d.map));

//	printf("nbrlen:%d\n", ft_nbrlen(ft_atoi("0")));
	printf("x:%d\n", d.x);
	printf("y:%d\n", d.y);
	printf("xlen:%d\n", d.xlen);
	printf("ylen:%d\n", d.ylen);
	printf("zmin:%d\n", d.zmin);
	printf("zmax:%d\n", d.zmax);
	printf("wire:\n");
	i = -1;
	while (++i < d.ylen)
	{
		j = -1;
		while (++j < d.xlen)
		{
			if (d.zmin < 0 && j == 0 && d.wire[i][j] > -1)
				printf(" ");
			if (d.wire[i][j] < 10)
				printf("%d  ", d.wire[i][j]);
			else
				printf("%d ", d.wire[i][j]);
		}
		printf("\n");
	}
}

int	ft_abs(int value)
{
	if (value < 0)
		return (-value);
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
		get_xlen(&d);
		process_map(&d);
		mlx.mlx = mlx_init();
		init_win(&d, d.xlen, d.ylen, 50);
		comment(d);
		mlx.win = mlx_new_window(mlx.mlx, d.x, d.y, "Hello fdf!");
		d.img = mlx_new_image(mlx.mlx, d.x, d.y);
		d.adr = mlx_get_data_addr(d.img, &d.bits, &d.line_len, &d.endian);
		draw_wire(&d);
		set_hooks(&mlx);
//		mlx_put_image_to_window(mlx.mlx, mlx.win, d.img, 0, ((d.y - (d.ylen + 1) * d.scale) / 2));
		mlx_put_image_to_window(mlx.mlx, mlx.win, d.img, 0, 100);
		mlx_loop(mlx.mlx);
		return (EXIT_SUCCESS);
	}
	perror("Missing file");
	return (EXIT_FAILURE);
}
