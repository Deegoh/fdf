/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/10 14:34:39 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	read_map(char *file, t_fdf *fdf)
{
	int		fd;
	char	*tmp;
	char	*sson;

	fd = open(file, O_RDONLY);
	if (fd < 0 || !ft_strnstr(file, ".fdf", ft_strlen(file)))
		display_err("File error");
	fdf->map.map = ft_strdup("");
	while (fd >= 0)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return ;
		sson = fdf->map.map;
		fdf->map.map = ft_strjoin(fdf->map.map, tmp);
		free(tmp);
		free(sson);
	}
	close(fd);
}

int	check_xlen(int *xlen)
{
//	int	i;
//
//	i = -1;
//	while (xlen[++i])
//		if (xlen[0] != xlen[i])
//			display_err("error size map");
	return (xlen[0]);
}
