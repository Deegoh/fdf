/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <tpinto-m@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/18 16:26:20 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	comment(t_fdf fdf)
{
	int	j;
	int	i;

	printf("map:\n%s", fdf.map.map);
//	printf("maplen:%d\n", ft_strlen(fdf.map.map));
//	printf("x:%d\n", fdf.map.x);
//	printf("y:%d\n", fdf.map.y);
//	printf("xlen:%d\n", fdf.map.xlen);
//	printf("ylen:%d\n", fdf.map.ylen);
//	printf("zmin:%d\n", fdf.map.zmin);
//	printf("zmax:%d\n", fdf.map.zmax);
	printf("\nwire:\n");
	i = -1;
	while (++i < fdf.map.ylen)
	{
		j = -1;
		while (++j < fdf.map.xlen)
		{
			if (fdf.map.wire[i][j] < 10)
				printf("%d ", fdf.map.wire[i][j]);
			else
				printf("%d ", fdf.map.wire[i][j]);
			// if (fdf.map.zmin < 0 && j == 0 && fdf.map.wire[i][j] > -1)
			// 	printf(" ");
		}
		printf("\n");
	}
	// printf("minx:%d\n", fdf.map.xmin);
	// printf("maxx:%d\n", fdf.map.xmax);
	// printf("maxy:%d\n", fdf.map.ymax);
	// printf("scale:%d\n", SCALE);
	// printf("scale:%d\n", fdf.cam.scale);
	// printf("scale:%d\n", fdf.cam.d_scale);
	// printf("\n");
	// printf("value test\n");
	// printf("endian:%d\n", fdf.endian);
	// printf("size_line:%d\n", fdf.line);
	// printf("bits_per_pixel:%d\n", fdf.bits);
}

// void	set_hooks(t_fdf *fdf)
// {
// 	mlx_hook(fdf->win, 2, 1L << 0, key_hook, fdf);
// 	mlx_hook(fdf->win, 17, 0, close_win, fdf);
// }

int	main(int ac, char *av[])
{
	t_fdf	fdf;

	if (ac > 2)
		display_err("Too much files");
	if (ac == 2)
	{
		printf("read map\n");
		fdf.map.xlen = 0;
		fdf.map.ylen = 0;
		read_map(av[1], &fdf);
		printf("end map\n");
		printf("process map\n");
		process_map(&fdf);
		printf("init struct\n");
		init_struct(&fdf);
		printf("search value\n");
		search_values(&fdf);
		printf("init win\n");
		init_win(&fdf, "Hello fdf!");
		comment(fdf);
		// put_wire(&fdf);
		// set_hooks(&fdf);
		// mlx_loop(fdf.mlx);
		return (EXIT_SUCCESS);
	}
	display_err("Missing file");
}
