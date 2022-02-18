/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/18 12:39:03 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->data_addr + (y * fdf->size_line + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_fdf *fdf, t_point b, t_point e, int color)
{
	double	deltax;
	double	deltay;
	double	pixelx;
	double	pixely;
	int		pixels;

	deltax = e.x - b.x;
	deltay = e.y - b.y;
	pixelx = b.x;
	pixely = b.y;
	pixels = (int)sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	while (pixels)
	{
		my_mlx_pixel_put(&fdf, (int)pixelx, (int)pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	iso(t_point	*p, int offset)
{
	double	previous_x;
	double	previous_y;

	previous_x = p->x;
	previous_y = p->y;
	p->x = (previous_x - previous_y) * cos(0.523599);
	p->y = -p->z + (previous_x + previous_y) * sin(0.523599);
	if (offset)
		p->x += offset;
}

t_point	create_point(int x, int y, int z)
{
	t_point	point;

	point.x = x * SCALE;
	point.y = y * SCALE;
	point.z = z;
	return (point);
}

void	draw_wire(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	b;
	t_point	e;
	int		x;

	x = ft_abs(fdf->map->xmin) + SCALE;
	j = -1;
	while (++j < fdf->map->ylen - 1)
	{
		i = -1;
		while (++i < fdf->map->xlen - 1)
		{
			b = create_point(i, j + 1, fdf->map->wire[j][i] * Z);
			e = create_point(i + 1, j + 1, fdf->map->wire[j][i + 1] * Z);
			iso(&b, x);
			iso(&e, x);
			draw_line(*fdf, b, e, 0x00FFFFFF);
			e = create_point(i, j + 2, fdf->map->wire[j + 1][i] * Z);
			iso(&e, x);
			draw_line(*fdf, b, e, 0x00FFFFFF);
		}
	}
}
