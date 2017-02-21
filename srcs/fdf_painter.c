/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_painter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 01:15:52 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/21 01:04:19 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int				i;

	if (x >= IMG_W || y >= IMG_H)
	{
		ft_printf("x = %d, y = %d\n", x, y);
		errors(2, "Out of bounds");
	}
	i = mlx->linesize * y + x * (mlx->bpp / 8);
	mlx->data[i] = color & 0xff;
	mlx->data[++i] = color >> 8 & 0xff;
	mlx->data[++i] = color >> 16;
}

static int			in_map(int x, int y, t_mlx *mlx)
{
	if (x * ZOOM + POS_X >= IMG_W || y * ZOOM + POS_Y >= IMG_H ||\
		x * ZOOM + POS_X < 0 || y * ZOOM + POS_Y < 0)
		return (0);
	return (1);
}

void				painter(t_mlx *mlx)
{
	int			y_count;
	int			x_count;
	t_point		(*web)[mlx->web_y][mlx->web_x];

	web = mlx->web;
	y_count = -1;
	while (++y_count < mlx->web_y && (x_count = -1))
		while (++x_count < mlx->web_x)
		{
			if (in_map(x_count, y_count, mlx))
				put_pixel(mlx, \
					x_count * ZOOM + POS_X, \
					y_count * ZOOM + POS_Y, \
				(*web)[y_count][x_count].color);
		}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img, 0, 0);
}

void				cleaner(t_mlx *mlx)
{
	int			y_count;
	int			x_count;
	t_point		(*web)[mlx->web_y][mlx->web_x];

	web = mlx->web;
	y_count = -1;
	while (++y_count < mlx->web_y && (x_count = -1))
		while (++x_count < mlx->web_x)
		{
			if (in_map(x_count, y_count, mlx))
				put_pixel(mlx, \
					x_count * ZOOM + POS_X, \
					y_count * ZOOM + POS_Y, \
					0);
		}
}

void				fdf_painter(const int y, const int x, t_point web[y][x])
{
	t_mlx		mlx;
	t_conv		conv;

	mlx.conv = &conv;
	mlx.web_x = x;
	mlx.web_y = y;
	mlx.web = web;
	mlx.mlx_ptr = mlx_init();
	conv.zoom = (IMG_W / x > IMG_H / y ? IMG_H / y : IMG_W / x);
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, WIN_NAME);
	mlx.img = mlx_new_image(mlx.mlx_ptr, IMG_W, IMG_H);
	mlx.data = mlx_get_data_addr(mlx.img, &(mlx.bpp), &(mlx.linesize), \
			&(mlx.endian));
	mlx_key_hook(mlx.win, keys, &mlx);
	mlx_mouse_hook(mlx.win, mouse, &mlx);
	painter(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
