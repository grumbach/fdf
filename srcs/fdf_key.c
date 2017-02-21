/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 10:53:58 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/21 01:04:13 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	position(t_mlx *mlx, int keycode)
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

int			keys(int keycode, void *param)
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
	else if (keycode == 78)
		unzoom(param);
	else if (keycode == 69)
		zoom(param);
	painter(param);
	return (0);
}
