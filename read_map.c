/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/10 10:18:39 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map(char *file, t_data *d)
{
	int		fd;
	char	*tmp;
	char	*sson;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	while (fd >= 0)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return ;
		sson = d->map;
		d->map = ft_strjoin(d->map, tmp);
		free(tmp);
		free(sson);
	}
	close(fd);
}



int	check_xlen(int *xlen)
{
	int	i;

	i = -1;
	while (xlen[++i])
	{
		if (xlen[0] != xlen[i])
		{
			printf("check_xlen i:%d xlen:%d\n", i, xlen[i]);
			exit(EXIT_FAILURE);
		}
	}
	return (xlen[0]);
}


