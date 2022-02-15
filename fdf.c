/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:58:40 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/15 15:13:36 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char *av[])
{
	t_vars	mlx;
	t_data	d;

	if (ac == 2)
	{
		d.map = ft_strdup("");
		read_map(av[1], &d);
		set_ylen(&d);
		set_xlen(&d);
		process_map(&d);
		init_win(&d, d.xlen, d.ylen, SCALE);
		search_values(&d);
		d.x = d.xmax + ft_abs(d.minminus) + SCALE * 4;
		d.y = d.ymax + SCALE;
		mlx.mlx = mlx_init();
		mlx.win = mlx_new_window(mlx.mlx, d.x, d.y, "Hello fdf!");
		d.img = mlx_new_image(mlx.mlx, d.x, d.y);
		d.adr = mlx_get_data_addr(d.img, &d.bits, &d.line_len, &d.endian);
		draw_wire(&d);
		set_hooks(&mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.win, d.img, 0, 0);
		mlx_loop(mlx.mlx);
		return (EXIT_SUCCESS);
	}
	display_err("Missing file");
}
