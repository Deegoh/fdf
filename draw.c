/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/28 17:09:05 by tpinto-m         ###   ########.fr       */
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
		my_mlx_pixel_put(fdf, (int)pixelx, (int)pixely, color);
		pixelx += deltax;
		pixely += deltay;
		--pixels;
	}
}

void	finish_draw_black(t_fdf *fdf)
{
	int		i;
	int		j;
	t_coor	pts;

	j = -1;
	while (++j < fdf->map.ylen - 1)
	{
		i = -1;
		while (++i < fdf->map.xlen - 1)
		{
			pts.b = create_point(i, fdf->map.ylen, fdf->map.wire[fdf->map.ylen - 1][i] * fdf->cam.z, fdf);
			pts.e = create_point(i + 1, fdf->map.ylen, fdf->map.wire[fdf->map.ylen - 1][i + 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			draw_line(fdf, pts.b, pts.e, 0x00000000);
			pts.b = create_point(fdf->map.xlen - 1, j + 1, fdf->map.wire[j][fdf->map.xlen - 1] * fdf->cam.z, fdf);
			pts.e = create_point(fdf->map.xlen - 1, j + 2, fdf->map.wire[j + 1][fdf->map.xlen - 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			draw_line(fdf, pts.b, pts.e, 0x00000000);
		}
	}
}

void	draw_wire_black(t_fdf *fdf)
{
	int		i;
	int		j;
	t_coor	pts;

	j = -1;
	while (++j < fdf->map.ylen - 1)
	{
		i = -1;
		while (++i < fdf->map.xlen - 1)
		{
			pts.b = create_point(i, j + 1, fdf->map.wire[j][i] * fdf->cam.z, fdf);
			pts.e = create_point(i + 1, j + 1, fdf->map.wire[j][i + 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			draw_line(fdf, pts.b, pts.e, 0x00000000);
			pts.b = create_point(i, j + 1, fdf->map.wire[j][i] * fdf->cam.z, fdf);
			pts.e = create_point(i, j + 2, fdf->map.wire[j + 1][i] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			draw_line(fdf, pts.b, pts.e, 0x00000000);
		}
	}
	finish_draw_black(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void	finish_draw(t_fdf *fdf)
{
	int		i;
	int		j;
	t_coor	pts;

	j = -1;
	while (++j < fdf->map.ylen - 1)
	{
		i = -1;
		while (++i < fdf->map.xlen - 1)
		{
			pts.b = create_point(i, fdf->map.ylen, fdf->map.wire[fdf->map.ylen - 1][i] * fdf->cam.z, fdf);
			pts.e = create_point(i + 1, fdf->map.ylen, fdf->map.wire[fdf->map.ylen - 1][i + 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			draw_line(fdf, pts.b, pts.e, get_color(fdf, pts.b, pts.e));
			pts.b = create_point(fdf->map.xlen - 1, j + 1, fdf->map.wire[j][fdf->map.xlen - 1] * fdf->cam.z, fdf);
			pts.e = create_point(fdf->map.xlen - 1, j + 2, fdf->map.wire[j + 1][fdf->map.xlen - 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			draw_line(fdf, pts.b, pts.e, get_color(fdf, pts.b, pts.e));
		}
	}
}

void	draw_wire(t_fdf *fdf)
{
	int		i;
	int		j;
	t_coor	pts;

	j = -1;
	while (++j < fdf->map.ylen - 1)
	{
		i = -1;
		while (++i < fdf->map.xlen - 1)
		{
			pts.b = create_point(i, j + 1, fdf->map.wire[j][i] * fdf->cam.z, fdf);
			pts.e = create_point(i + 1, j + 1, fdf->map.wire[j][i + 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			draw_line(fdf, pts.b, pts.e, get_color(fdf, pts.b, pts.e));
			pts.b = create_point(i, j + 1, fdf->map.wire[j][i] * fdf->cam.z, fdf);
			pts.e = create_point(i, j + 2, fdf->map.wire[j + 1][i] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			draw_line(fdf, pts.b, pts.e, get_color(fdf, pts.b, pts.e));
		}
	}
	finish_draw(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
