/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:30:21 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/04 13:45:15 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

int	get_default_color(int z, t_fdf *fdf)
{
	double	percentage;

	percentage = percent(fdf->map.zmin, fdf->map.zmax, z);
	if (percentage < 0.2)
		return (COLOR5);
	else if (percentage < 0.4)
		return (COLOR4);
	else if (percentage < 0.6)
		return (COLOR3);
	else if (percentage < 0.8)
		return (COLOR2);
	else
		return (COLOR1);
}
//
//int	get_color(t_fdf *fdf, t_point b, t_point e)
//{
//	int	range;
//	int	color;
//	int	seg;
//
//	range = (ft_abs(fdf->map.zmin) + ft_abs(fdf->map.zmax)) * fdf->cam.z;
//	if (b.z == 0 && e.z == 0)
//		return (0x00FFFFFF);
//	seg = 255 / range;
//	range = ft_abs(b.z) + ft_abs(e.z);
//	color = range * seg;
//	return (color);
//}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_point current, t_point start, t_point end, t_point delta)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF,
					(end.color >> 16) & 0xFF,
					percentage);
	green = get_light((start.color >> 8) & 0xFF,
					  (end.color >> 8) & 0xFF,
					  percentage);
	blue = get_light(start.color & 0xFF,
					 end.color & 0xFF,
					 percentage);
	return ((red << 16) | (green << 8) | blue);
}
