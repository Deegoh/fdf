/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:53:06 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/02 18:53:33 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_nbrlen(int nbr)
{
	int	i;

	i = 1;
	if (nbr < 0)
	{
		nbr = -nbr;
		i++;
	}
	if (nbr == 0)
		return (i);
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i - 1);
}

int	get_value_map(const char *tmp, int *i)
{
	int	ret;

	if (!tmp)
		return (0);
	ret = 0;
	while (tmp[*i] == ' ')
		*i = *i + 1;
	if (tmp[*i] == '\n')
		*i = *i + 1;
	if (ft_atoi((tmp + *i)))
	{
		ret = ft_atoi((tmp + *i));
		*i = *i + ft_nbrlen(ret);
	}
	else if (ft_atoi((tmp + *i)) == 0)
		*i = *i + 1;
	return (ret);
}

int	check_z(int value, t_data *d)
{
	if (value < d->zmin)
		d->zmin = value;
	if (value > d->zmax)
		d->zmax = value;
	return (value);
}

void	process_map(t_data *d)
{
	int	**new_map;
	int	i;
	int	j;
	int	k;

	new_map = malloc(d->ylen * sizeof(int *));
	if (!new_map)
		return ;
	j = 0;
	k = 0;
	while (j < d->ylen)
	{
		i = 0;
		new_map[j] = malloc(d->xlen * sizeof(int));
		if (!new_map[j])
			return ;
		while (i < d->xlen)
			new_map[j][i++] = check_z(get_value_map(d->map, &k), d);
		j++;
	}
	d->wire = new_map;
}
