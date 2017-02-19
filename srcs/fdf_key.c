/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 10:53:58 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/19 11:12:49 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			keys(int keycode, void *param)
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
