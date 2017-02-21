/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_painter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 01:15:52 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/21 17:33:32 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			in_map(int x_count, int y_count, t_mlx *mlx)
{
	t_point		(*web)[mlx->web_y][mlx->web_x];

	web = mlx->web;
	if (XPUT >= IMG_W || YPUT >= IMG_H || XPUT < 0 || YPUT < 0)
		return (0);
	return (1);
}

static t_xy			there(t_mlx *mlx, int x_count, int y_count)
{
	t_xy		there;
	t_point		(*web)[mlx->web_y][mlx->web_x];

	web = mlx->web;
	there = (t_xy){XPUT, YPUT};
	return (there);
}

void				painter(t_mlx *mlx)
{
	int			y_count;
	int			x_count;
	t_xy		here;
	t_point		(*web)[mlx->web_y][mlx->web_x];

	web = mlx->web;
	y_count = -1;
	while (++y_count < mlx->web_y && (x_count = -1))
		while (++x_count < mlx->web_x)
		{
			here = (t_xy){XPUT, YPUT};
			if (in_map(x_count, y_count, mlx))
			{
				put_pixel(mlx, here.x, here.y, (*web)[y_count][x_count].color);
				if (x_count + 1 < mlx->web_x && \
					in_map(x_count + 1, y_count, mlx))
					put_line(mlx, here, there(mlx, x_count + 1, y_count), \
					get_colorful(mlx, x_count + 1, y_count));
				if (y_count + 1 < mlx->web_y && \
					in_map(x_count, y_count + 1, mlx))
					put_line(mlx, here, there(mlx, x_count, y_count + 1), \
					get_colorful(mlx, x_count, y_count + 1));
			}
		}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img, -100, -100);
}

void				cleaner(t_mlx *mlx)
{
	int			y_count;
	int			x_count;
	t_xy		here;
	t_point		(*web)[mlx->web_y][mlx->web_x];

	web = mlx->web;
	y_count = -1;
	while (++y_count < mlx->web_y && (x_count = -1))
		while (++x_count < mlx->web_x)
		{
			here = (t_xy){XPUT, YPUT};
			if (in_map(x_count, y_count, mlx))
			{
				put_pixel(mlx, XPUT, YPUT, 0);
				if (x_count + 1 < mlx->web_x && \
					in_map(x_count + 1, y_count, mlx))
					put_line(mlx, here, there(mlx, x_count + 1, y_count), 0);
				if (y_count + 1 < mlx->web_y && \
					in_map(x_count, y_count + 1, mlx))
					put_line(mlx, here, there(mlx, x_count, y_count + 1), 0);
			}
		}
}

void				fdf_painter(const int y, const int x, t_point web[y][x])
{
	t_mlx		mlx;
	t_conv		conv;

	ft_bzero(&conv, sizeof(t_conv));
	ft_bzero(&mlx, sizeof(t_mlx));
	mlx.conv = &conv;
	mlx.web_x = x;
	mlx.web_y = y;
	mlx.web = web;
	mlx.mlx_ptr = mlx_init();
	conv.zoom = (WIN_W / x > WIN_H / y ? WIN_H / y : WIN_W / x);
	conv.angle_x = 3;
	conv.angle_y = 3;
	conv.pos_x = 100;
	conv.pos_y = 100;
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, WIN_NAME);
	mlx.img = mlx_new_image(mlx.mlx_ptr, IMG_W, IMG_H);
	mlx.data = mlx_get_data_addr(mlx.img, &(mlx.bpp), &(mlx.linesize), \
			&(mlx.endian));
	mlx_key_hook(mlx.win, keys, &mlx);
	mlx_mouse_hook(mlx.win, mouse, &mlx);
	painter(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
