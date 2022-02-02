/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/02 18:36:47 by tpinto-m         ###   ########.fr       */
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

void	iso(int *x, int *y, int z)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	draw_wire(t_data *data)
{
	int		i;
	int		j;
	t_point	b;
	t_point	e;

	j = -1;
	while (++j < data->ylen - 1)
	{
		i = -1;
		while (++i < data->xlen - 1)
		{
			b.s = data->scale;
			b.x = i * b.s;
			b.y = j * b.s;
			b.z = data->wire[j][i] * 4;
			e.s = data->scale;
			e.x = (i + 1) * e.s;
			e.y = j * e.s;
			e.z = data->wire[j][i + 1] * 4;
			iso(&b.x, &b.y, b.z);
			iso(&e.x, &e.y, e.z);
			b.x += (data->ylen * data->scale);
			e.x += (data->ylen * data->scale);
			draw_line(*data, b, e, 0x00FFFFFF);
			e.x = i * e.s;
			e.y = (j + 1) * e.s;
			e.z = data->wire[j + 1][i] * 4;
			iso(&e.x, &e.y, e.z);
			e.x += (data->ylen * data->scale);
			draw_line(*data, b, e, 0x00FFFFFF);
		}
	}
}
