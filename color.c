/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:30:21 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/07 16:04:54 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_percent(int start, int end, int current)
{
	double	placement;
	double	distance;
	double	tot;

	placement = current - start;
	distance = end - start;
	tot = placement / distance;
	if (distance == 0)
		tot = 1.0;
	return (tot);
}

int	get_default_color(int z, t_fdf *fdf)
{
	double	percentage;

	percentage = ft_percent(fdf->map.zmin, fdf->map.zmax, z);
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
		percentage = ft_percent(start.x, end.x, current.x);
	else
		percentage = ft_percent(start.y, end.y, current.y);
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
