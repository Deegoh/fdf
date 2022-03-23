/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:15:17 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/23 17:12:05 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_one_line(t_fdf *fdf)
{
	int		i;
	t_coor	pts;

	i = -1;
	while (++i < fdf->map.xlen - 1)
	{
		pts.b = new_pts(i, 1, fdf->map.wire[0][i][0], fdf);
		pts.e = new_pts(i + 1, 1, fdf->map.wire[0][i + 1][0], fdf);
		pts.b.color = fdf->map.wire[0][i][1];
		rot_all(fdf, &pts);
		isocoor(fdf, &pts);
		put_line(fdf, pts.b, pts.e, pts.b.color);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
