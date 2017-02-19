/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_painter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 01:15:52 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/19 09:33:32 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int			keys(int keycode, void *param)
{
	ft_printf("keycode press = %d\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_image(((t_mlx *)param)->mlx_ptr, ((t_mlx *)param)->img);
		mlx_destroy_window(((t_mlx *)param)->mlx_ptr, ((t_mlx *)param)->win);
		exit(1);
	}
	// if (keycode == 126)//U
	// if (keycode == 125)//D
	// if (keycode == 123)//L
	// if (keycode == 124)//R
	return (0);
}

static void			put_pixel(t_mlx *mlx, double x, double y, int color)
{
	int				i;

	if (x >= IMG_W || y >= IMG_H)
		errors(0, "Out of bounds");
	i = mlx->linesize * y + x * 4;
	mlx->star[i] = color & 0xff;
	mlx->star[++i] = color >> 8 & 0xff;
	mlx->star[++i] = color >> 16;
}

static void			starcraft(const int y, const int x, t_point web[y][x], \
					t_mlx *mlx)
{
	int			y_count;
	int			x_count;

	y_count = -1;
	while (++y_count < y && (x_count = -1))
		while (++x_count)
			put_pixel(mlx, x, y, web[y_count][x_count].color);
}

void 			fdf_painter(const int y, const int x, t_point web[y][x])
{
	t_mlx		mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, WIN_NAME);
	mlx.img = mlx_new_image(mlx.mlx_ptr, IMG_W, IMG_H);
	mlx.star = mlx_get_data_addr(mlx.img, &(mlx).bpp, &(mlx).linesize, \
			&(mlx).endian);
	starcraft(y, x, web, &mlx);
	mlx_key_hook(mlx.win, keys, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx_ptr);
}
