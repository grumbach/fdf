/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 03:34:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/19 16:32:51 by agrumbac         ###   ########.fr       */
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
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				linesize;
	int				endian;
}					t_mlx;

char				*fdf_reader_checker(const char *file, int *y, int *x);
void 				fdf_parser(const int y, const int x, t_point web[y][x], \
					const char *read);
void 				fdf_painter(const int y, const int x, t_point web[y][x]);
long				errors(const int err, const char *name);

void				put_pixel(t_mlx *mlx, int x, int y, int color);
int					mouse(int button, int x, int y, void *param);
int					keys(int keycode, void *param);

# define WIN_NAME "fdf"
# define WIN_W 1000
# define WIN_H 1000
# define IMG_W 1000
# define IMG_H 1000

# define DEFAULT_COLOR 0x00ff00

#endif
