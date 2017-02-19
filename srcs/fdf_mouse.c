/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 10:53:38 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/19 18:49:24 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom(void *param)
{
	((t_mlx *)param)->zoom += 1;
}

static void	unzoom(void *param)
{
	((t_mlx *)param)->mlx_ptr -= 1;
}

int			mouse(int button, int x, int y, void *param)
{
	ft_printf("mouse [x%d][y%d]: %d\n", x, y, button);
	if (button == 1)
	{
		put_pixel(param, x, y, DEFAULT_COLOR);
	}
	else if (button == 4)
		zoom(param);
	else if (button == 5)
		unzoom(param);
	mlx_put_image_to_window(((t_mlx *)param)->mlx_ptr, \
	((t_mlx *)param)->win, ((t_mlx *)param)->img, 0, 0);
	return (0);
}
