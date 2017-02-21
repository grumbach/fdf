/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 03:34:25 by agrumbac          #+#    #+#             */
/*   Updated: 2017/02/21 10:52:38 by agrumbac         ###   ########.fr       */
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

typedef struct		s_conv
{
	double			zoom;
	double			pos_x;
	double			pos_y;
	double			angle_x;
	double			angle_y;
}					t_conv;

typedef struct		s_mlx
{
	void			*web;
	t_conv			*conv;
	void			*mlx_ptr;
	void			*win;
	void			*img;
	char			*data;
	int				web_x;
	int				web_y;
	int				bpp;
	int				linesize;
	int				endian;
}					t_mlx;

typedef struct		s_bresenham
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_bresenham;

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

char				*fdf_reader_checker(const char *file, int *y, int *x);
void 				fdf_parser(const int y, const int x, t_point web[y][x], \
					const char *read);
void 				fdf_painter(const int y, const int x, t_point web[y][x]);
long				errors(const int err, const char *name);
void				put_pixel(t_mlx *mlx, int x, int y, int color);
void				put_line(t_mlx *mlx, t_xy a, t_xy b, int color);
void				painter(t_mlx *mlx);
void				cleaner(t_mlx *mlx);
int					mouse(int button, int x, int y, void *param);
int					keys(int keycode, void *param);
void				zoom(t_mlx *mlx);
void				unzoom(t_mlx *mlx);

# define WIN_NAME "fdf"
# define WIN_W 1024
# define WIN_H 632
# define IMG_W 1024
# define IMG_H 632

# define DEFAULT_COLOR 0x00ff00

# define Z ((*web)[y_count][x_count]).z
# define ZOOM ((t_conv*)(mlx->conv))->zoom
# define POS_X ((t_conv*)(mlx->conv))->pos_x
# define POS_Y ((t_conv*)(mlx->conv))->pos_y
# define ANGLE_X ((t_conv*)(mlx->conv))->angle_x
# define ANGLE_Y ((t_conv*)(mlx->conv))->angle_y
# define XPUT x_count * ZOOM + POS_X + Z * ANGLE_X
# define YPUT y_count * ZOOM + POS_Y + Z * ANGLE_Y

#endif
