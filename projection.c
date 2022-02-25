/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:21:08 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/25 20:21:08 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	iso(t_point	*p, int xoffset, int yoffset)
{
	double	previous_x;
	double	previous_y;

	previous_x = p->x;
	previous_y = p->y;
	p->x = (previous_x - previous_y) * cos(0.523599);
	p->y = -p->z + (previous_x + previous_y) * sin(0.523599);
	if (xoffset)
		p->x += xoffset;
	if (yoffset)
		p->y += yoffset;
}

void	isocoor(t_fdf *fdf, t_coor	*pts)
{
	int		x;
	int		y;

	x = ft_abs(fdf->map.xmin) + fdf->cam.scale + fdf->cam.xoffset;
	y = fdf->cam.yoffset;
	iso(&pts->b, x, y);
	iso(&pts->e, x, y);
}

t_point	create_point(int x, int y, int z, t_fdf *fdf)
{
	t_point	point;

	point.x = x * fdf->cam.scale;
	point.y = y * fdf->cam.scale;
	point.z = z;
	return (point);
}
