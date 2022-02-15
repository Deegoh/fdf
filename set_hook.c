/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:07:53 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/01/31 10:37:26 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_hook(int mousecode, int x, int y, t_vars *vars)
{
	(void)vars;
	(void)mousecode;
	(void)x;
	(void)y;
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		close_win(vars);
	return (0);
}

void	set_hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, key_hook, vars);
	mlx_hook(vars->win, 17, 0, close_win, vars);
}
