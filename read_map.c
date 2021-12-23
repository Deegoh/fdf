/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/23 13:18:10 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	read_map(char *file, t_data *d)
{
	int		fd;
	char	*tmp;
	char	*help;
	int		line;

	fd = open(file, O_RDONLY);
	line = 0;
	if (fd < 0)
		return (0);
	while (fd >= 0)
	{
		tmp = get_next_line(fd);
		if (count_line(tmp))
			d->line_len = count_line(tmp);
		if (!tmp)
			return (line);
		help = d->map;
		d->map = ft_strjoin(d->map, tmp);
		free(tmp);
		free(help);
		line++;
	}
	return (0);
}

int	ft_nbtlen(int nbr)
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

int	count_line(const char *tmp)
{
	int	i;
	int	count;

	if (!tmp)
		return (0);
	i = 0;
	count = 0;
	while (tmp[i])
	{
		while (tmp[i] == ' ')
			i++;
		if (ft_atoi((tmp + i)))
		{
			count++;
			i += ft_nbtlen(tmp[i]);
		}
		else if (ft_atoi((tmp + i)) == 0)
		{
			count++;
			i++;
		}
	}
	return (count);
}

//void	process_map(t_data *d)
//{
//	char	**new_map;
//	int		i;
//	int		j;
//
//	new_map = malloc(d->line * sizeof(char *));
//	if (!*new_map)
//		return ;
//	i = 0;
//	j = 0;
//	while (j < d->line)
//	{
//		new_map = malloc(d->line * sizeof(char *));
//		if (!new_map)
//			return ;
//		while (i < d->line_len)
//		{
//			new_map[j][i] = atoi(d->map);
//			i++;
//		}
//		j++;
//	}
//}