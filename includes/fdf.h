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

# define WIDTH 800
# define HEIGHT 600

# define ESC_1_KEYCODE 53
# define ESC_2_KEYCODE 65307

typedef struct s_point {
	int		x;
	int		y;
	int		z;
	int32_t	color;
}	t_point;

typedef struct s_camera {
	double	x;
	double	y;
	double	z;
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
	t_camera	camera;
	t_data		img;
}	t_fdf;

void	draw_pixel(t_data *data, int x, int y, int color);
void	draw_line(t_data *data, t_point start, t_point end, int color);

int32_t	create_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b);
uint8_t	get_t(int32_t trgb);
uint8_t	get_r(int32_t trgb);
uint8_t	get_g(int32_t trgb);
uint8_t	get_b(int32_t trgb);

#endif /* FDF_H */
