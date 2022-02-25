/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:07:53 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/25 19:21:47 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move(int keycode, t_fdf *fdf)
{
	if (keycode == W)
		fdf->cam.yoffset -= 10;
	if (keycode == S)
		fdf->cam.yoffset += 10;
	if (keycode == A)
		fdf->cam.xoffset -= 10;
	if (keycode == D)
		fdf->cam.xoffset += 10;
}

void	scale(int keycode, t_fdf *fdf)
{
	if (keycode == Q)
		fdf->cam.z -= 1;
	if (keycode == E)
		fdf->cam.z += 1;
	if (keycode == R)
		fdf->cam.scale += 1;
	if (keycode == F)
		fdf->cam.scale -= 1;
}

void	reset(int keycode, t_fdf *fdf)
{
	if (keycode == SPACE)
	{
		fdf->cam.scale = SCALE;
		fdf->cam.z = Z;
		fdf->cam.yoffset = (1080 - fdf->map.ymax) / 2;
		fdf->cam.xoffset = (1920 - (fdf->map.xmax + ft_abs(fdf->map.xmin))) / 2;
		fdf->cam.alpha = 0;
		fdf->cam.beta = 0;
		fdf->cam.gamma = 0;
	}
}

void	rot(int keycode, t_fdf *fdf)
{
	if (keycode == I)
		fdf->cam.alpha += 0.05;
	if (keycode == K)
		fdf->cam.alpha -= 0.05;
	if (keycode == J)
		fdf->cam.beta += 0.05;
	if (keycode == L)
		fdf->cam.beta -= 0.05;
	if (keycode == U)
		fdf->cam.gamma += 0.05;
	if (keycode == O)
		fdf->cam.gamma -= 0.05;
}

int	key_hook(int keycode, t_fdf *fdf)
{
	draw_wire(fdf, 0x00000000);
	if (keycode == ESC)
		close_win(fdf);
	scale(keycode, fdf);
	move(keycode, fdf);
	rot(keycode, fdf);
	reset(keycode, fdf);
	draw_wire(fdf, 0x00FFFFFF);
	return (0);
}
