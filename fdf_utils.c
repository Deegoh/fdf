/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:56:37 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/15 13:46:53 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	set_min_value(int x, int px)
{
	if (px > x)
		return (x);
	return (px);
}

int	set_max_value(int x, int px)
{
	if (px < x)
		return (x);
	return (px);
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

int	close_win(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(EXIT_SUCCESS);
}
