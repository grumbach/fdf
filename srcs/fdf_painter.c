/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_painter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 01:15:52 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/19 16:58:27 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int				i;

	if (x >= IMG_W || y >= IMG_H)
		errors(2, "Out of bounds");
	i = mlx->linesize * y + x * 4;
	mlx->data[i] = color & 0xff;
	mlx->data[++i] = color >> 8 & 0xff;
	mlx->data[++i] = color >> 16;
}

static void			painter(const int y, const int x, t_point web[y][x], \
					t_mlx *mlx)
{
	int			y_count;
	int			x_count;

	y_count = -1;
	while (++y_count < y && (x_count = -1))
		while (++x_count < x)
			put_pixel(mlx, x_count * 2, y_count * 2, \
				web[y_count][x_count].color);
}

void				fdf_painter(const int y, const int x, t_point web[y][x])
{
	t_mlx		mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, WIN_NAME);
	mlx.img = mlx_new_image(mlx.mlx_ptr, IMG_W, IMG_H);
	mlx.data = mlx_get_data_addr(mlx.img, &(mlx).bpp, &(mlx).linesize, \
			&(mlx).endian);
	painter(y, x, web, &mlx);
	mlx_key_hook(mlx.win, keys, &mlx);
	mlx_mouse_hook(mlx.win, mouse, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx_ptr);
}
