/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:30:21 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/09 14:34:43 by tpinto-m         ###   ########.fr       */
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
	if (percentage < 0.16)
		return (RED);
	else if (percentage < 0.33)
		return (SAFFRON);
	else if (percentage < 0.5)
		return (YELLOW);
	else if (percentage < 0.66)
		return (AO);
	else if (percentage < 0.83)
		return (BLUE);
	else
		return (VIOLET);
}
