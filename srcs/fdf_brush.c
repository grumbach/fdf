/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_brush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 02:44:04 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/22 22:58:31 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					get_colorful(t_mlx *mlx, int x_count, int y_count)
{
	int				color;

	t_point(*web)[mlx->web_y][mlx->web_x];
	web = mlx->web;
	color = DEFAULT_COLOR;
	if (COLOR != DEFAULT_COLOR)
		color = COLOR;
	if (++x_count < mlx->web_x)
		if (COLOR != DEFAULT_COLOR)
			color = COLOR;
	x_count--;
	if (++y_count < mlx->web_y)
		if (COLOR != DEFAULT_COLOR)
			color = COLOR;
	y_count -= 2;
	if (y_count > 0)
		if (COLOR != DEFAULT_COLOR)
			color = COLOR;
	y_count++;
	x_count--;
	if (x_count > 0)
		if (COLOR != DEFAULT_COLOR)
			color = COLOR;
	return (color);
}

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

void				put_line(t_mlx *mlx, t_xy a, t_xy b, int color)
{
	t_bresenham		badass;

	badass.dx = abs(b.x - a.x);
	badass.sx = a.x < b.x ? 1 : -1;
	badass.dy = abs(b.y - a.y);
	badass.sy = a.y < b.y ? 1 : -1;
	badass.err = (badass.dx > badass.dy ? badass.dx : -badass.dy) / 2;
	badass.e2 = badass.err;
	while (1)
	{
		put_pixel(mlx, a.x, a.y, color);
		if (a.x == b.x && a.y == b.y)
			break ;
		badass.e2 = badass.err;
		if (badass.e2 > -badass.dx)
		{
			badass.err -= badass.dy;
			a.x += badass.sx;
		}
		if (badass.e2 < badass.dy)
		{
			badass.err += badass.dx;
			a.y += badass.sy;
		}
	}
}
