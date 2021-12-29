/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/28 21:12:55 by tpinto-m         ###   ########.fr       */
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
		{
			if (line > 0 && d->xlen != count_line(tmp))
				printf("invalide map / readmap()\n");
			d->xlen = count_line(tmp);
		}
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

int	test_line(const char *tmp, int *i)
{
	int	ret;

	if (!tmp)
		return (0);
	ret = 0;
	while (tmp[*i] == ' ')
	{
		*i = *i + 1;
	}
	if (ft_atoi((tmp + *i)))
	{
		ret = ft_atoi((tmp + *i));
		*i += ft_nbtlen(tmp[*i]);
	}
	else if (ft_atoi((tmp + *i)) == 0)
	{
		*i = *i + 1;
	}
//	printf("%d ", ret);
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
		{
			new_map[j][i] = test_line(d->map, &k);
//			printf("[%d]", new_map[j][i]);
//			if (new_map[j][i] == 0)
//				printf(" ");
			i++;
		}
//		printf("\n");
		j++;
	}
	d->wire = new_map;
}
