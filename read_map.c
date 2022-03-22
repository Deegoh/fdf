/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <tpinto-m@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/22 16:33:26 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*parse_line(char *gnl, t_fdf *fdf)
{
	int	i;
	int	count;

	if (!gnl)
		return (NULL);
	i = -1;
	count = 1;
	while (gnl[++i])
	{
		if (gnl[i] == ' ' && i == 0)
		{
			while (gnl[i] == ' ')
				i++;
		}
		if (gnl[i] == ' ' && ft_isalnum(gnl[i + 1]))
			count++;
		else if (gnl[i] == ' ' && gnl[i + 1] == '-' && ft_isalnum(gnl[i + 2]))
			count++;
	}
	if (!fdf->map.xlen)
		fdf->map.xlen = count;
	if (fdf->map.xlen != count)
		display_err("error x len map");
	fdf->map.ylen++;
	return (gnl);
}

void	read_map(char *file, t_fdf *fdf)
{
	int		fd;
	char	*tmp;
	char	*sson;

	fd = open(file, O_RDONLY);
	if (fd <= 0 || !ft_strnstr(file, ".fdf", ft_strlen(file)))
		display_err("File error");
	fdf->map.map = ft_strdup("");
	while (fd >= 0)
	{
		tmp = parse_line(get_next_line(fd), fdf);
		if (!tmp)
			return ;
		sson = fdf->map.map;
		fdf->map.map = ft_strjoin(fdf->map.map, tmp);
		free(tmp);
		free(sson);
	}
	close(fd);
}

int	check_hex(const char	*map)
{
	int	i;

	i = 0;
	while (map[i] != ' ' && map[i] != '\0')
	{
		i++;
	}
	return (i);
}
