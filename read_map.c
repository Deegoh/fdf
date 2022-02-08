/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/08 16:23:22 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//TODO CHECK MAP
//TODO ERROR DISPLAY
//		if (count_line(tmp))
//		{
//			if (line > 0 && d->xlen != count_line(tmp))
//				printf("invalide map / readmap()\n");
//			d->xlen = count_line(tmp);
//		}

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

void	get_ylen(t_data *d)
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

void	get_xlen(t_data *d)
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
