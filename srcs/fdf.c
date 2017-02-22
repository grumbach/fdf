/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 03:33:07 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/23 00:30:17 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		overmind(const char *read, const int y, const int x)
{
	t_point		web[y][x];
	int			y_count;
	int			x_count;

	y_count = -1;
	while (++y_count < y && (x_count = -1))
		while (++x_count < x)
		{
			web[y_count][x_count].z = 0;
			web[y_count][x_count].color = DEFAULT_COLOR;
		}
	fdf_parser(y, x, web, read);
	ft_memdel((void**)&read);
	fdf_painter(y, x, web);
}

int				main(int ac, char **av)
{
	int			y;
	int			x;
	char		*read;

	x = 0;
	y = 0;
	if (ac > 1)
	{
		if (!(read = fdf_reader_checker(av[1], &y, &x)))
			errors(3, av[1]);
		else
			overmind(read, y, x);
	}
	else
		errors(1, 0);
	return (0);
}

long			errors(const int err, const char *name)
{
	ft_putstr_fd("fdf: ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" ", 2);
	}
	if (err == 0)
		ft_putendl_fd(strerror(errno), 2);
	else if (err == 1)
		ft_putstr_fd("\nUsage: fdf [file]\n", 2);
	else if (err == 2)
		ft_putstr_fd("\n", 2);
	else if (err == 3)
		ft_putstr_fd(" : Invalid map\n", 2);
	exit(1);
	return (0);
}
