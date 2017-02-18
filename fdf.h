/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 03:34:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/18 16:30:29 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include "mlx.h"

typedef	struct		s_point
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_point;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win;
	void			*img;
	char			*star;
	int				bpp;//bitperpixel
	int				linesize;//linesize
	int				endian;
}					t_mlx;

char				*fdf_reader_checker(const char *file, int *y, int *x);
void 				fdf_parser(const int y, const int x, t_point web[y][x], \
					const char *read);
void 				fdf_painter(const int y, const int x, t_point web[y][x]);
long				errors(const int err, const char *name);

# define WIN_NAME "also sprach fdf!"
# define WIN_W 1000
# define WIN_H 1000
# define IMG_W 1000
# define IMG_H 1000

#endif
