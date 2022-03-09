/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:56:37 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/09 11:47:04 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_min(int value1, int value2)
{
	if (value2 > value1)
		return (value1);
	return (value2);
}

int	ft_max(int value1, int value2)
{
	if (value2 < value1)
		return (value1);
	return (value2);
}

int	ft_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

void	display_err(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	close_win(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit(EXIT_SUCCESS);
}
