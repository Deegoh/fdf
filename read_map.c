/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <tpinto-m@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/18 16:44:53 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*parse_line(char *gnl, t_fdf *fdf)
{
	int i;
	int count;
	static int test = 1;

	if (!gnl)
		return (NULL);
	i = -1;
	count = 1;
	while(gnl[++i])
		if(gnl[i] == ' ' && ft_isdigit(gnl[i + 1]))
			count++;
	if (!fdf->map.xlen)
		fdf->map.xlen = count;
	if (fdf->map.xlen != count)
	{
		printf("gnl:\n%s", gnl);
		printf("\nmap:\n%s", fdf->map.map);
		printf("test%d\n", test);
		printf("count%d\n", count);
		printf("xlen%d\n", fdf->map.xlen);
		display_err("error x len map");
	}
	test++;
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
	while (map[i] != ' ')
	{
		i++;
	}
	return (i);
}

int	check_xlen(int *xlen)
{
	// int	i;

	// i = -1;
	// while (xlen[++i])
	// 	if (xlen[0] != xlen[i])
	// 		display_err("error size map");
	return (xlen[0]);
}
