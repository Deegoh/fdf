/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <tpinto-m@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:42:52 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/22 16:14:48 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_struct(t_fdf *fdf)
{
	fdf->map.xmin = 0;
	fdf->map.xmax = 0;
	fdf->map.ymax = 0;
	fdf->cam.z = Z;
	fdf->cam.xoffset = 0;
	fdf->cam.yoffset = 0;
	fdf->cam.scale = SCALE;
	fdf->cam.alpha = 0;
	fdf->cam.beta = 0;
	fdf->cam.gamma = 0;
	fdf->cam.view = 0;
}

void	init_win(t_fdf *fdf, char *str)
{
	fdf->map.x = fdf->map.xmax + ft_abs(fdf->map.xmin) + SCALE * 4;
	fdf->map.y = fdf->map.ymax + SCALE;
	if (fdf->map.xmax == 0 && fdf->map.xmin == 0)
		fdf->map.xmax = 20;
	fdf->cam.d_scale = HEIGHT / (ft_abs(fdf->map.xmax) + ft_abs(fdf->map.xmin));
	fdf->cam.scale = fdf->cam.d_scale;
	fdf->mlx = mlx_init();
	fdf->map.x = WIDTH;
	fdf->map.y = HEIGHT;
	fdf->cam.xoffset = (WIDTH - (fdf->map.xmax + ft_abs(fdf->map.xmin))) / 2;
	fdf->cam.yoffset = (HEIGHT - fdf->map.ymax) / 4;
	fdf->win = mlx_new_window(fdf->mlx, fdf->map.x, fdf->map.y, str);
	fdf->img = mlx_new_image(fdf->mlx, fdf->map.x, fdf->map.y);
	fdf->addr = mlx_addr(fdf->img, &fdf->bits, &fdf->line, &fdf->endian);
}

void	search_values(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	b;

	j = -1;
	while (++j < fdf->map.ylen)
	{
		i = -1;
		while (++i < fdf->map.xlen)
		{
			b.x = i * SCALE;
			b.y = j * SCALE;
			b.z = fdf->map.wire[j][i] * fdf->cam.z;
			iso(&b, 0, 0, fdf->cam.view);
			fdf->map.xmin = ft_min(b.x, fdf->map.xmin);
			fdf->map.xmax = ft_max(b.x, fdf->map.xmax);
			fdf->map.ymax = ft_max(b.y, fdf->map.ymax);
		}
	}
}
