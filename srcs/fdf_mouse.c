/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mouse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 10:53:38 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/21 01:04:22 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		zoom(t_mlx *mlx)
{
	ZOOM += 1;
}

void		unzoom(t_mlx *mlx)
{
	if (ZOOM > 1)
		ZOOM -= 1;
}

int			mouse(int button, int x, int y, void *param)
{
	ft_printf("mouse [x%d][y%d]: %d\n", x, y, button);
	cleaner(param);
	if (button == 4)
		zoom(param);
	else if (button == 5)
		unzoom(param);
	painter(param);
	return (0);
}
