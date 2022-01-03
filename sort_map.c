/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 15:53:06 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/31 01:25:37 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_nbrlen(int nbr)
{
	int	i;

	i = 0;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
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
		*i += ft_nbrlen(tmp[*i]);
	}
	else if (ft_atoi((tmp + *i)) == 0)
		*i = *i + 1;
	return (ret);
}

void	process_map(t_data *d)
{
	int	**new_map;
	int	i;
	int	j;
	int	k;

	new_map = malloc(d->ylen * sizeof(int *));
	if (!*new_map)
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
			new_map[j][i++] = get_value_map(d->map, &k);
		j++;
	}
	d->wire = new_map;
}
