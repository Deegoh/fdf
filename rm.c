/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:54:16 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/23 17:12:05 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rm_finish_wire(t_fdf *fdf)
{
	int		i;
	int		j;
	t_coor	pts;
	t_point	len;

	j = -1;
	len.x = fdf->map.xlen - 1;
	len.y = fdf->map.ylen - 1;
	while (++j < fdf->map.ylen - 1)
	{
		i = -1;
		while (++i < fdf->map.xlen - 1)
		{
			pts.b = new_pts(i, len.y + 1, fdf->map.wire[len.y][i][0], fdf);
			pts.e = new_pts(i + 1, len.y + 1, fdf->map.wire[len.y][i + 1][0], fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e, BLACK);
			pts.b = new_pts(len.x, j + 1, fdf->map.wire[j][len.x][0], fdf);
			pts.e = new_pts(len.x, j + 2, fdf->map.wire[j + 1][len.x][0], fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e, BLACK);
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
			pts.b = new_pts(i, j + 1, fdf->map.wire[j][i][0], fdf);
			pts.e = new_pts(i + 1, j + 1, fdf->map.wire[j][i + 1][0], fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e, BLACK);
			pts.b = new_pts(i, j + 1, fdf->map.wire[j][i][0], fdf);
			pts.e = new_pts(i, j + 2, fdf->map.wire[j + 1][i][0], fdf);
			rot_all(fdf, &pts);
			isocoor(fdf, &pts);
			put_line(fdf, pts.b, pts.e, BLACK);
		}
	}
	rm_finish_wire(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void	rm_one_line(t_fdf *fdf)
{
	int		i;
	t_coor	pts;

	i = -1;
	while (++i < fdf->map.xlen - 1)
	{
		pts.b = new_pts(i, 1, fdf->map.wire[0][i][0], fdf);
		pts.e = new_pts(i + 1, 1, fdf->map.wire[0][i + 1][0], fdf);
		rot_all(fdf, &pts);
		isocoor(fdf, &pts);
		put_line(fdf, pts.b, pts.e, BLACK);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
