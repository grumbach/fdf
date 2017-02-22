/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_painter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 01:15:52 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/23 00:27:04 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			in_map(t_xy here)
{
	if (here.x >= IMG_W || here.y >= IMG_H || here.x < 0 || here.y < 0)
		return (0);
	return (1);
}

static t_xy			there(t_mlx *mlx, int x_count, int y_count)
{
	t_xy		there;
	t_point		(*web)[mlx->web_y][mlx->web_x];

	there = (t_xy){0, 0};
	web = mlx->web;
	if (mlx->projection == 1)
		there = (t_xy){XPUT + POS_X, YPUT + POS_Y};
	else if (mlx->projection == 2)
		there = (t_xy){XISO + POS_X, YISO + POS_Y};
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
			here = there(mlx, x_count, y_count);
			if (in_map(here))
			{
				put_pixel(mlx, here.x, here.y, (*web)[y_count][x_count].color);
				if (x_count + 1 < mlx->web_x && \
					in_map(there(mlx, x_count + 1, y_count)))
					put_line(mlx, here, there(mlx, x_count + 1, y_count), \
					get_colorful(mlx, x_count + 1, y_count));
				if (y_count + 1 < mlx->web_y && \
					in_map(there(mlx, x_count, y_count + 1)))
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
			here = there(mlx, x_count, y_count);
			if (in_map(here))
			{
				put_pixel(mlx, here.x, here.y, 0);
				if (x_count + 1 < mlx->web_x && \
					in_map(there(mlx, x_count + 1, y_count)))
					put_line(mlx, here, there(mlx, x_count + 1, y_count), 0);
				if (y_count + 1 < mlx->web_y && \
					in_map(there(mlx, x_count, y_count + 1)))
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
	mlx.projection = 1;
	mlx.web_x = x;
	mlx.web_y = y;
	mlx.web = web;
	mlx.mlx_ptr = mlx_init();
	conv.zoom = (WIN_W / x > WIN_H / y ? WIN_H / y : WIN_W / x);
	conv.angle_x = -2;
	conv.angle_y = -2;
	conv.pos_x = 100;
	conv.pos_y = 100;
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, WIN_NAME);
	mlx.img = mlx_new_image(mlx.mlx_ptr, IMG_W, IMG_H);
	mlx.data = mlx_get_data_addr(mlx.img, &(mlx.bpp), &(mlx.linesize), \
			&(mlx.endian));
	mlx_hook(mlx.win, 2, 3, keys, &mlx);
	mlx_mouse_hook(mlx.win, mouse, &mlx);
	painter(&mlx);
	mlx_loop(mlx.mlx_ptr);
}
