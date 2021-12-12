/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:01 by tpinto-m          #+#    #+#             */
/*   Updated: 2021/12/12 19:42:10 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int read_map(char *file, char **gnl)
{
	int fd;
	char *tmp;
	char *help;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (fd >= 0)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			return (1);
		help = *gnl;
		*gnl = ft_strjoin(*gnl, tmp);
		free(help);
	}
	return (1);
}