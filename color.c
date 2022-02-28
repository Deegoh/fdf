/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:30:21 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/28 16:55:33 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(t_fdf *fdf, t_point b, t_point e)
{
	int	range;
	int	color;
	int	seg;

	range = (ft_abs(fdf->map.zmin) + ft_abs(fdf->map.zmax)) * fdf->cam.z;
	if (b.z == 0 && e.z == 0)
		return (0x00FFFFFF);
	seg = 16777215 / range;
	range = ft_abs(b.z) + ft_abs(e.z);
	color = range * seg;
	return (color);
}