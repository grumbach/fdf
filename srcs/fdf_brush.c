/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_brush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 02:44:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/21 09:37:04 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int				i;

	if (x >= IMG_W || y >= IMG_H || x < 0 || y < 0)
	{
		ft_printf("x = %d, y = %d\n", x, y);
		return ;
		errors(2, "Out of bounds");
	}
	i = mlx->linesize * y + x * (mlx->bpp / 8);
	mlx->data[i] = color & 0xff;
	mlx->data[++i] = color >> 8 & 0xff;
	mlx->data[++i] = color >> 16;
}

void				put_line(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	t_bresenham		badass;

	badass.dx = abs(x1 - x0);
	badass.sx = x0 < x1 ? 1 : -1;
	badass.dy = abs(y1 - y0);
	badass.sy = y0 < y1 ? 1 : -1;
	badass.err = (badass.dx > badass.dy ? badass.dx : -badass.dy) / 2;
	badass.e2 = badass.err;
	while (1)
	{
		put_pixel(mlx, x0, y0, DEFAULT_COLOR);
		if (x0 == x1 && y0 == y1)
			break ;
		badass.e2 = badass.err;
		if (badass.e2 > -badass.dx)
		{
			badass.err -= badass.dy;
			x0 += badass.sx;
		}
		if (badass.e2 < badass.dy)
		{
			badass.err += badass.dx;
			y0 += badass.sy;
		}
	}
}
