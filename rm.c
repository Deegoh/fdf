/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:54:16 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/04 13:17:04 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//void	rm_line(t_fdf *fdf, t_point b, t_point e)
//{
//	double	deltax;
//	double	deltay;
//	double	pixelx;
//	double	pixely;
//	int		pixels;
//
//	deltax = e.x - b.x;
//	deltay = e.y - b.y;
//	pixelx = b.x;
//	pixely = b.y;
//	pixels = (int)sqrt((deltax * deltax) + (deltay * deltay));
//	deltax /= pixels;
//	deltay /= pixels;
//	while (pixels)
//	{
//		put_pixel(fdf, (int)pixelx, (int)pixely, BLACK);
//		pixelx += deltax;
//		pixely += deltay;
//		--pixels;
//	}
//}
void	rm_line(t_fdf *fdf, t_point b, t_point e)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta.x = ft_abs(b.x - e.x);
	delta.y = ft_abs(b.y - e.y);
	sign.x = e.x < b.x ? 1 : -1;
	sign.y = e.y < b.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = e;
	while (cur.x != b.x || cur.y != b.y)
	{
		put_pixel(fdf, cur.x, cur.y, BLACK);
		if ((error[1] = error[0] * 2) > -delta.y)
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

void	rm_finish_wire(t_fdf *fdf)
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
			rm_line(fdf, pts.b, pts.e);
			pts.b = new_point(fdf->map.xlen - 1, j + 1, fdf->map.wire[j][fdf->map.xlen - 1] * fdf->cam.z, fdf);
			pts.e = new_point(fdf->map.xlen - 1, j + 2, fdf->map.wire[j + 1][fdf->map.xlen - 1] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			rm_line(fdf, pts.b, pts.e);
		}
	}
}

void	rm_wire(t_fdf *fdf)
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
			rm_line(fdf, pts.b, pts.e);
			pts.b = new_point(i, j + 1, fdf->map.wire[j][i] * fdf->cam.z, fdf);
			pts.e = new_point(i, j + 2, fdf->map.wire[j + 1][i] * fdf->cam.z, fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			rm_line(fdf, pts.b, pts.e);
		}
	}
	rm_finish_wire(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
