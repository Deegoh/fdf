/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/07 15:50:44 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int	dst;

	if (x <= 1920 && x >= 0 && y <= 1080 && y >= 0)
	{
		dst = (y * fdf->size_line + x * (fdf->bits_per_pixel / 8));
		fdf->data_addr[dst] = color;
		fdf->data_addr[++dst] = color >> 8;
		fdf->data_addr[++dst] = color >> 16;
	}
}

void	put_line(t_fdf *fdf, t_point b, t_point e)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta.x = ft_abs(b.x - e.x);
	delta.y = ft_abs(b.y - e.y);
	if (e.x < b.x)
		sign.x = 1;
	else
		sign.x = -1;
	if (e.y < b.y)
		sign.y = 1;
	else
		sign.y = -1;
	error[0] = delta.x - delta.y;
	cur = e;
	while (cur.x != b.x || cur.y != b.y)
	{
		put_pixel(fdf, cur.x, cur.y, get_color(cur, b, e, delta));
		error[1] = error[0] * 2;
		if ((error[1]) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void	put_lastwire(t_fdf *fdf)
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
			pts.b = new_point(i, fdf->map.ylen, fdf->map.wire[fdf->map.ylen - 1][i] * fdf->cam.z, fdf);
			pts.e = new_point(i + 1, fdf->map.ylen, fdf->map.wire[fdf->map.ylen - 1][i + 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e);
			pts.b = new_point(fdf->map.xlen - 1, j + 1, fdf->map.wire[j][fdf->map.xlen - 1] * fdf->cam.z, fdf);
			pts.e = new_point(fdf->map.xlen - 1, j + 2, fdf->map.wire[j + 1][fdf->map.xlen - 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e);
		}
	}
}

void	put_wire(t_fdf *fdf)
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
			pts.b = new_point(i, j + 1, fdf->map.wire[j][i] * fdf->cam.z, fdf);
			pts.e = new_point(i + 1, j + 1, fdf->map.wire[j][i + 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e);
			pts.b = new_point(i, j + 1, fdf->map.wire[j][i] * fdf->cam.z, fdf);
			pts.e = new_point(i, j + 2, fdf->map.wire[j + 1][i] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e);
		}
	}
	put_lastwire(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
