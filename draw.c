/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:10:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/09 14:19:55 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int	dst;

	if (x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0)
	{
		dst = (y * fdf->line + x * (fdf->bits / 8));
		fdf->addr[dst] = color;
		fdf->addr[++dst] = color >> 8;
		fdf->addr[++dst] = color >> 16;
	}
}

void	sign_pts(t_point *sign, t_point b, t_point e)
{
	if (e.x < b.x)
		sign->x = 1;
	else
		sign->x = -1;
	if (e.y < b.y)
		sign->y = 1;
	else
		sign->y = -1;
}

void	put_line(t_fdf *fdf, t_point b, t_point e, int color)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta.x = ft_abs(b.x - e.x);
	delta.y = ft_abs(b.y - e.y);
	sign_pts(&sign, b, e);
	error[0] = delta.x - delta.y;
	cur = e;
	while (cur.x != b.x || cur.y != b.y)
	{
		put_pixel(fdf, cur.x, cur.y, color);
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
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
	t_point	len;

	j = -1;
	len.x = fdf->map.xlen - 1;
	len.y = fdf->map.ylen - 1;
	while (++j < len.y)
	{
		i = -1;
		while (++i < len.x)
		{
			pts.b = new_pts(i, len.y + 1, fdf->map.wire[len.y][i], fdf);
			pts.e = new_pts(i + 1, len.y + 1, fdf->map.wire[len.y][i + 1], fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e, pts.b.color);
			pts.b = new_pts(len.x, j + 1, fdf->map.wire[j][len.x], fdf);
			pts.e = new_pts(len.x, j + 2, fdf->map.wire[j + 1][len.x], fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e, pts.b.color);
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
			pts.b = new_pts(i, j + 1, fdf->map.wire[j][i], fdf);
			pts.e = new_pts(i + 1, j + 1, fdf->map.wire[j][i + 1], fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e, pts.b.color);
			pts.b = new_pts(i, j + 1, fdf->map.wire[j][i], fdf);
			pts.e = new_pts(i, j + 2, fdf->map.wire[j + 1][i], fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e, pts.b.color);
		}
	}
	put_lastwire(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
