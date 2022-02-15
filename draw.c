/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/14 20:19:13 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->adr + (y * data->line_len + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_data d, t_point b, t_point e, int color)
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
		my_mlx_pixel_put(&d, (int)pixelx, (int)pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	iso(t_point	*p)
{
	double	previous_x;
	double	previous_y;

	previous_x = p->x;
	previous_y = p->y;
	p->x = (previous_x - previous_y) * cos(0.523599);
	p->y = -p->z + (previous_x + previous_y) * sin(0.523599);
}

void	draw_wire(t_data *data)
{
	int		i;
	int		j;
	t_point	b;
	t_point	e;
	int		x = ft_abs(data->minminus) + SCALE;

	j = -1;
	while (++j < data->ylen - 1)
	{
		i = -1;
		while (++i < data->xlen - 1)
		{
			b.x = i * SCALE;
			b.y = (j + 1) * SCALE;
			b.z = data->wire[j][i] * Z;
			e.x = (i + 1) * SCALE;
			e.y = (j + 1) * SCALE;
			e.z = data->wire[j][i + 1] * Z;
			iso(&b);
			iso(&e);
			b.x += x;
			e.x += x;
			draw_line(*data, b, e, 0x00FFFFFF);
			e.x = i * SCALE;
			e.y = (j + 2) * SCALE;
			e.z = data->wire[j + 1][i] * Z;
			iso(&e);
			e.x += x;
			draw_line(*data, b, e, 0x00FFFFFF);
		}
	}
}
