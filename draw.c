/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/01/31 17:49:14 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->adr + (y * data->line_len + x * (data->bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_line2(t_data d, t_point b, t_point e, int color)
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

t_point	iso(t_point p, int i)
{
	t_point	np;
	int		previous_x;
	int		previous_y;

	previous_x = p.x;
	previous_y = p.y;
	if (i == 1)
		previous_y = p.y + p.s;
	else if (i == 2)
		previous_x = p.x + p.s;
	else if (i == 3)
	{
		previous_y = p.y + p.s;
		previous_x = p.x + p.s;
	}
	else if (i == -1)
		previous_y = p.y - p.s;
	else if (i == -2)
		previous_x = p.x - p.s;
	np.x = (previous_x - previous_y) * cos(0.523599);
	np.y = (previous_x + previous_y) * sin(0.523599);
	return (np);
}

void	draw_point(t_data *data, t_point p, int color)
{
	p.s = p.s / 2;
	draw_line2(*data, iso(p, 0), iso(p, 1), color);
	draw_line2(*data, iso(p, 0), iso(p, 2), color);
	draw_line2(*data, iso(p, 0), iso(p, -1), color);
	draw_line2(*data, iso(p, 0), iso(p, -2), color);
}

void	draw_point2(t_data *data, t_point p, int color)
{
	p.s = p.s / 2;
	draw_line2(*data, iso(p, 0), iso(p, 2), color);
	draw_line2(*data, iso(p, 0), iso(p, 1), color);
	draw_line2(*data, iso(p, 0), iso(p, -1), color);
	draw_line2(*data, iso(p, 0), iso(p, -2), color);
}

void	draw_wire2(t_data *data)
{
	int		i;
	int		j;
	t_point	p;

	j = -1;
	while (++j < data->ylen)
	{
		i = -1;
		while (++i < data->xlen)
		{
			p.s = data->scale;
			p.x = i * p.s;
			p.y = j * p.s;
			if (data->wire[j][i])
				draw_point(data, p, 0x00065CCC); //0x00FF0000
			else
				draw_point2(data, p, 0x00FFFFFF); //0x00FFFFFF
		}
	}
}

void	draw_wire(t_data *data)
{
	int		i;
	int		j;
	t_point	b;
	t_point	e;

	j = -1;
	while (++j < data->ylen)
	{
		i = -1;
		while (++i < data->xlen)
		{
			b.s = data->scale;
			b.x = i * b.s;
			b.y = j * b.s;
			b.z = data->wire[j][i];
			e.s = data->scale;
			e.x = (i + 1) * e.s;
			e.y = j * e.s;
			e.z = data->wire[j][i];
			draw_line2(*data, b, e, 0x00FFFFFF); //0x00FF0000
			e.x = i * e.s;
			e.y = (j + 1) * e.s;
			draw_line2(*data, b, e, 0x00FFFFFF); //0x00FF0000
		}
	}
}
