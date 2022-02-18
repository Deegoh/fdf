/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:07:53 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/18 17:02:07 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_hook(int mousecode, int x, int y, t_fdf *fdf)
{
	(void)fdf;
	(void)mousecode;
	(void)x;
	(void)y;
	return (0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == ESC)
		close_win(fdf);
//	if (keycode == Q)
//		Z = Z + 1;
//	if (keycode == E)
//		Z += -1;
	return (0);
}

void	set_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->win, 17, 0, close_win, fdf);
}
