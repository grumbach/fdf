/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 10:53:58 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/23 00:15:44 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		reset(t_mlx *mlx)
{
	int			y_count;
	int			x_count;

	t_point(*web)[mlx->web_y][mlx->web_x];
	web = mlx->web;
	y_count = -1;
	while (++y_count < mlx->web_y && (x_count = -1))
		while (++x_count < mlx->web_x)
			COLOR = DEFAULT_COLOR;
	ZOOM = (WIN_W / mlx->web_x > WIN_H / mlx->web_y ? WIN_H / mlx->web_y : \
			WIN_W / mlx->web_x);
	POS_X = 100;
	POS_Y = 100;
	ANGLE_X = 0;
	ANGLE_Y = 0;
}

static void		colorise(t_mlx *mlx, int keycode)
{
	int			y_count;
	int			x_count;
	int			col;

	t_point(*web)[mlx->web_y][mlx->web_x];
	web = mlx->web;
	srand(time(NULL));
	col = rand();
	y_count = -1;
	while (++y_count < mlx->web_y && (x_count = -1))
		while (++x_count < mlx->web_x)
		{
			if (keycode == 49)
				COLOR = (COLOR + col) % 0xffffff + Z * 42;
			else
				COLOR = (COLOR + rand()) % 0xffffff;
		}
}

static void		position(t_mlx *mlx, int keycode)
{
	if (keycode == 126)
		POS_Y -= 10;
	if (keycode == 125)
		POS_Y += 10;
	if (keycode == 123)
		POS_X -= 10;
	if (keycode == 124)
		POS_X += 10;
}

static void		angle(t_mlx *mlx, int keycode)
{
	if (keycode == 13)
		ANGLE_Y -= 1;
	if (keycode == 1)
		ANGLE_Y += 1;
	if (keycode == 0)
		ANGLE_X -= 1;
	if (keycode == 2)
		ANGLE_X += 1;
	if (keycode == 18)
		mlx->projection = 1;
	if (keycode == 19)
		mlx->projection = 2;
}

int				keys(int keycode, void *param)
{
	ft_printf("keycode press = %d\n", keycode);
	cleaner(param);
	if (keycode == 53)
	{
		mlx_destroy_image(((t_mlx *)param)->mlx_ptr, ((t_mlx *)param)->img);
		mlx_destroy_window(((t_mlx *)param)->mlx_ptr, ((t_mlx *)param)->win);
		exit(1);
	}
	else if ((keycode <= 126) && (keycode >= 123))
		position(param, keycode);
	else if (((keycode >= 0) && (keycode <= 2)) || keycode == 13 || \
			keycode == 18 || keycode == 19)
		angle(param, keycode);
	else if (keycode == 78)
		unzoom(param);
	else if (keycode == 69)
		zoom(param);
	else if (keycode == 49 || keycode == 48)
		colorise(param, keycode);
	else if (keycode == 51)
		reset(param);
	painter(param);
	return (0);
}
