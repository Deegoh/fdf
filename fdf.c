/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/22 18:37:28 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	comment(t_fdf fdf)
{
	int	j;
	int	i;

	printf("map:\n%s", fdf.map.map);
	printf("maplen:%d\n", ft_strlen(fdf.map.map));
	printf("x:%d\n", fdf.map.x);
	printf("y:%d\n", fdf.map.y);
	printf("xlen:%d\n", fdf.map.xlen);
	printf("ylen:%d\n", fdf.map.ylen);
	printf("zmin:%d\n", fdf.map.zmin);
	printf("zmax:%d\n", fdf.map.zmax);
	printf("wire:\n");
	i = -1;
	while (++i < fdf.map.ylen)
	{
		j = -1;
		while (++j < fdf.map.xlen)
		{
			if (fdf.map.zmin < 0 && j == 0 && fdf.map.wire[i][j] > -1)
				printf(" ");
			if (fdf.map.wire[i][j] < 10)
				printf("%d  ", fdf.map.wire[i][j]);
			else
				printf("%d ", fdf.map.wire[i][j]);
		}
		printf("\n");
	}
	printf("minminus:%d\n", fdf.map.xmin);
	printf("maxx:%d\n", fdf.map.xmax);
	printf("maxy:%d\n", fdf.map.ymax + 100);
//	printf("testx:%d\n", fdf.map.xmax + ft_abs(fdf.map.xmin) + 200);
}

int	main(int ac, char *av[])
{
	t_fdf	fdf;

	if (ac == 2)
	{
		fdf.map.map = ft_strdup("");
		read_map(av[1], &fdf);
		set_ylen(&fdf);
		set_xlen(&fdf);
		process_map(&fdf);
		init_struct(&fdf, fdf.map.xlen, fdf.map.ylen, SCALE);
		search_values(&fdf);
		comment(fdf);
		init_win(&fdf, "Hello fdf!");
		draw_wire(&fdf, 0x00FFFFFF);
		set_hooks(&fdf);
		mlx_loop(fdf.mlx);
	}
	display_err("Missing file");
}
