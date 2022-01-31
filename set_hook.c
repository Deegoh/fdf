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
//	printf("mouseCode:%d\n", mousecode);
	if (mousecode == 1)
	{
		printf("x:%d\n", x);
		printf("y:%d\n", y);
	}
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
//	printf("p:%p\n", vars->mlx);
//	printf("keycode:%d\n", keycode);
	if (keycode == ESC)
		close_win(vars);
	if (keycode == SPACE)
		printf("space\n");
	if (keycode == W)
		printf("w\n");
	if (keycode == S)
		printf("s\n");
	if (keycode == A)
		printf("a\n");
	if (keycode == D)
		printf("d\n");
	return (0);
}

void	set_hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, key_hook, vars);
	mlx_hook(vars->win, 17, 0, close_win, vars);
	mlx_hook(vars->win, 5, 0, mouse_hook, vars);
}
