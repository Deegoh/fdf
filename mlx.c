/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-m <marvin@24lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:42:16 by tpinto-m          #+#    #+#             */
/*   Updated: 2022/03/22 16:14:48 by tpinto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*mlx_addr(void *img_ptr, int *bits, int *size, int *endian)
{
	return (mlx_get_data_addr(img_ptr, bits, size, endian));
}
