/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 23:10:35 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/18 15:26:14 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 			fdf_parser(const int y, const int x, t_point web[y][x], \
					const char *read)
{
	int		y_count;
	int		x_count;

	y_count = -1;
	while (++y_count < y && (x_count = -1))
	{
		while (++x_count < x)
		{
			while (*read != '\n' && (*read == ' ' || *read == '\t'))
				read++;
			web[y_count][x_count].z = ft_atoi(read);
			while (*read != '\n' && (ft_isdigit(*read) || *read == '-'))
				read++;
			if (*read == ',')
			{
				read++;
				web[y_count][x_count].color = ft_atoi_base(read, 16);
				while (*read != '\n' && ft_strchr("xABCDEF1234567890", *read))
					read++;
			}
			web[y_count][x_count].x = x_count;
			read++;
		}
		web[y_count][x_count].y = y_count;
	}
}
