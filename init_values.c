/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 11:42:52 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/11 20:43:38 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_win(t_data *img, int size_x, int size_y, int scale)
{
	img->x = (size_x + 0) * scale * 1.4;
//	img->x = 22 * scale;
	img->y = (size_y + 0) * scale * 1.4;
	img->scale = scale;
}

int	set_min_minus(int x, int px)
{
	if (px > x)
		return (x);
	return (px);
}

void	set_xlen(t_data *d)
{
	int	*xlen;
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	xlen = ft_calloc(sizeof(xlen), d->ylen);
	len = ft_strlen(d->map);
	while (++i < len)
	{
		if (d->map[i] == ' ')
			continue ;
		if (d->map[i] == '\n')
		{
			j++;
			continue ;
		}
		if (ft_atoi(&d->map[i]) || (ft_atoi(&d->map[i]) == 0 && ft_isdigit(d->map[i])))
		{
			i += ft_nbrlen(ft_atoi(&d->map[i])) - 1;
			xlen[j]++;
		}
	}
	d->xlen = check_xlen(xlen);
}

void	set_ylen(t_data *d)
{
	int	ylen;
	int	i;

	ylen = 0;
	i = 0;
	while (d->map[i])
	{
		if (d->map[i] == '\n' && d->map[i + 1])
			ylen++;
		i++;
	}
	d->ylen = ylen + 1;
}

void	search_min_minus(t_data *data)
{
	int		i;
	int		j;
	t_point	b;
	int		z = 4;

	j = -1;
	while (++j < data->ylen - 1)
	{
		i = -1;
		while (++i < data->xlen - 1)
		{
			b.s = data->scale;
			b.x = i * b.s;
			b.y = j * b.s + data->scale * 2;
			b.z = data->wire[j][i] * z;
			iso(&b.x, &b.y, b.z);
			data->minminus = set_min_minus(b.x, data->minminus);
		}
	}
}
