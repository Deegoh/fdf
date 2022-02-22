/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:07:53 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/02/22 18:33:59 by tpinto-m         ###   ########.fr       */
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
		fdf->cam.yoffset = 0;
		fdf->cam.xoffset = 0;
//		fdf->cam.alpha = 0;
//		fdf->cam.beta = 0;
//		fdf->cam.gamma = 0;
	}
}

void	rot(int keycode, t_fdf *fdf)
{
	(void)fdf;
	if (keycode == UP)
		printf("hello\n");
	if (keycode == DOWN)
		printf("hello\n");
	if (keycode == LEFT)
		printf("hello\n");
	if (keycode == RIGHT)
		printf("hello\n");
}

int	key_hook(int keycode, t_fdf *fdf)
{
	draw_wire(fdf, 0x00000000);
	if (keycode == ESC)
		close_win(fdf);
	scale(keycode, fdf);
	move(keycode, fdf);
//	rot(keycode, fdf);
	reset(keycode, fdf);
	draw_wire(fdf, 0x00FFFFFF);
	return (0);
}

void	set_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, key_hook, fdf);
	mlx_hook(fdf->win, 17, 0, close_win, fdf);
}
