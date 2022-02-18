/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:42:52 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/15 15:12:56 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_win(t_fdf *fdf, int size_x, int size_y, int scale)
{
	fdf->map->x = (size_x + 0) * scale * 1.4;
	fdf->map->y = (size_y + 0) * scale * 1.4;
	fdf->map->xmin = 0;
	fdf->map->xmax = 0;
	fdf->map->ymax = 0;
}

void	set_xlen(t_fdf *fdf)
{
	int	*xlen;
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	xlen = ft_calloc(sizeof(xlen), fdf->map->ylen);
	len = ft_strlen(fdf->map->map);
	while (++i < len)
	{
		if (fdf->map->map[i] == ' ')
			continue ;
		if (fdf->map->map[i] == '\n')
		{
			j++;
			continue ;
		}
		if (ft_isdigit(fdf->map->map[i]))
		{
			i += ft_nbrlen(ft_atoi(&fdf->map->map[i])) - 1;
			xlen[j]++;
		}
	}
	fdf->map->xlen = check_xlen(xlen);
}

void	set_ylen(t_fdf *fdf)
{
	int	ylen;
	int	i;

	ylen = 0;
	i = 0;
	while (fdf->map->map[i])
	{
		if (fdf->map->map[i] == '\n' && fdf->map->map[i + 1])
			ylen++;
		i++;
	}
	fdf->map->ylen = ylen + 1;
}

void	search_values(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	b;

	j = -1;
	while (++j < fdf->map->ylen - 1)
	{
		i = -1;
		while (++i < fdf->map->xlen - 1)
		{
			b.x = i * SCALE;
			b.y = (j + 2) * SCALE;
			b.z = fdf->map->wire[j][i] * Z;
			iso(&b, 0);
			fdf->map->xmin = ft_min(b.x, fdf->map->xmin);
			fdf->map->xmax = ft_max(b.x, fdf->map->xmax);
			fdf->map->ymax = ft_max(b.y, fdf->map->ymax);
		}
	}
}
