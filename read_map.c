/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/02 19:18:35 by tpinto-m         ###   ########.fr       */
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

void	get_xlen(char *file, t_data *d)
{
	int		xlen;
	int		fd;
	int		i;
	char	*tmp;

	fd = open(file, O_RDONLY);
	if (fd >= 0)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return ;
		i = -1;
		xlen = 0;
		while (tmp[++i])
		{
			while (tmp[i] == ' ')
				i++;
			if (ft_atoi(tmp + i) || ft_atoi(tmp + i) == 0)
			{
				i = i + ft_nbrlen(ft_atoi(tmp + i));
				d->xlen++;
			}
			d->xlen = xlen;
		}
		free(tmp);
	}
	close(fd);
}
