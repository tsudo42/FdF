/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define FRAME_RATE 16
# define ZOOM_RATE 1.1
# define MOVE_RATE 20

# define MAX_ZOOM_RATE 1e4
# define MIN_ZOOM_RATE 1e-4
# define MAX_MOVE_VAL 1e4

# define ESC_1_KEYCODE 53
# define ESC_2_KEYCODE 65307
# define SPACE_KEYCODE 32
# define P_KEYCODE 112
# define H_KEYCODE 104
# define L_KEYCODE 108
# define W_KEYCODE 119
# define A_KEYCODE 97
# define S_KEYCODE 115
# define D_KEYCODE 100
# define J_KEYCODE 106
# define K_KEYCODE 107
# define I_KEYCODE 105
# define U_KEYCODE 117
# define M_KEYCODE 109
# define Y_KEYCODE 121
# define T_KEYCODE 116

typedef struct s_point {
	int		raw_x;
	int		raw_y;
	int		raw_z;
	int32_t	color;
	double	dx;
	double	dy;
	int32_t	color_alt;
}	t_point;

typedef struct s_camera {
	double	parallel_x;
	double	parallel_y;
	double	z_rate;
	double	magnify_rate;
	double	r_xy;
	double	r_xy_sin;
	double	r_xy_cos;
	double	r_z;
	double	r_z_cos;
	int		minimap;
}	t_camera;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_fdf {
	void		*mlx;
	void		*win;
	t_point		**map;
	int			map_width;
	int			map_height;
	t_camera	camera;
	t_data		img;
}	t_fdf;

/* loading */
int		is_empty_line(const char *line);
void	load_file(t_fdf *fdf, const char *filename);
void	load_point(t_point *point, char *token, int x, int y);
void	load_file_eof(int fd, const char *error_msg);

/* color */
int32_t	create_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b);
int32_t	mix_color(int32_t start_color, int32_t end_color, double rate);
void	set_altcolor(t_fdf *fdf);

/* drawing */
void	reset_screen(t_fdf *fdf);
void	draw_pixel(t_data *data, int x, int y, int color);
void	draw_line(t_fdf *fdf, t_data *data, t_point start, t_point end);
void	draw_fdf(t_fdf *fdf);
void	draw_minimap(t_fdf *fdf);

/* camera */
int		reset_camera(t_fdf *fdf);
void	rotate_camera(t_fdf *fdf, int direction_key);
void	move_camera(t_fdf *fdf, int zoomrate_key);
void	zoom_camera(t_fdf *fdf, int zoomrate_key);
void	change_z_altitude_camera(t_fdf *fdf, int direction_key);
void	dist_camera(t_fdf *fdf, int dist_key);
void	add_camera_effect(t_fdf *fdf, t_point *point);

/* hook */
int		key_hook(int keycode, t_fdf *fdf);

/* main */
int		fdf_close(t_fdf *fdf);

#endif /* FDF_H */
