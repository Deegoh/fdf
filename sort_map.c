/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <tpinto-m@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:53:06 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/22 16:40:23 by tpinto-m         ###   ########.fr       */
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

int	get_value_map(const char *tmp, long *i)
{
	int	ret;

	if (!tmp || !(tmp + *i))
		return (0);
	ret = 0;
	if (tmp[*i] == ',')
		*i = *i + check_hex(tmp + *i);
	while (tmp[*i] == ' ')
		*i = *i + 1;
	if (tmp[*i] == '\n')
		*i = *i + 1;
	if (ft_atoi(tmp + *i))
		ret = ft_atoi((tmp + *i));
	*i = *i + ft_nbrlen(ret);
	return (ret);
}

int	check_z(int value, t_fdf *fdf)
{
	if (value < fdf->map.zmin)
		fdf->map.zmin = value;
	if (value > fdf->map.zmax)
		fdf->map.zmax = value;
	return (value);
}

void	process_map(t_fdf *fdf)
{
	int		**new_map;
	int		i;
	int		j;
	long	k;

	new_map = malloc(fdf->map.ylen * sizeof(int *));
	if (!new_map)
		return ;
	j = 0;
	k = 0;
	while (j < fdf->map.ylen)
	{
		i = 0;
		new_map[j] = malloc(fdf->map.xlen * sizeof(int));
		if (!new_map[j])
			return ;
		while (i < fdf->map.xlen)
			new_map[j][i++] = check_z(get_value_map(fdf->map.map, &k), fdf);
		j++;
	}
	fdf->map.wire = new_map;
}
