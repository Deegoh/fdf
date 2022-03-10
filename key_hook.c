/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:07:53 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/10 17:00:54 by tpinto-m         ###   ########.fr       */
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
	if (keycode == KEY_UP)
		fdf->cam.yoffset -= 100;
	if (keycode == KEY_DOWN)
		fdf->cam.yoffset += 100;
	if (keycode == KEY_LEFT)
		fdf->cam.xoffset -= 100;
	if (keycode == KEY_RIGHT)
		fdf->cam.xoffset += 100;
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
	int	xoff;

	if (keycode == SPACE)
	{
		fdf->cam.yoffset = (HEIGHT - fdf->map.ymax) / 4;
		xoff = (WIDTH - (fdf->map.xmax + ft_abs(fdf->map.xmin))) / 2;
		fdf->cam.xoffset = xoff;
		fdf->cam.scale = fdf->cam.d_scale;
		fdf->cam.z = Z;
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
	rm_wire(fdf);
	if (keycode == ESC)
		close_win(fdf);
	scale(keycode, fdf);
	move(keycode, fdf);
	rot(keycode, fdf);
	view(keycode, fdf);
	reset(keycode, fdf);
	put_wire(fdf);
	return (0);
}