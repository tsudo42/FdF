/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	if (x >= WIDTH || y >= HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_point	mix_point(t_point start, t_point end, long step_i, long step_total)
{
	double	step_rate;
	long	color[4];
	long	color_tmp;
	int		i;

	if (step_total == 0)
		return (start);
	step_rate = (double)step_i / step_total;
	start.dx = start.dx * step_rate + end.dx * (1 - step_rate);
	start.dy = start.dy * step_rate + end.dy * (1 - step_rate);
	i = 0;
	while (i < 4)
	{
		color[i] = ((start.color >> ((3 - i) * 8)) & 0xFF);
		color_tmp = ((end.color >> ((3 - i) * 8)) & 0xFF);
		color[i] = color[i] + (color_tmp - color[i]) * step_i / step_total;
		if (color[i] < 0)
			color[i] = 0;
		if (color[i] > UINT8_MAX)
			color[i] = UINT8_MAX;
		i++;
	}
	start.color = create_trgb(color[0], color[1], color[2], color[3]);
	return (start);
}

void	add_camera_effect(t_fdf *fdf, t_point *point)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	tmp_x = (point->raw_x - fdf->map_width / 2) * 10;
	tmp_y = (point->raw_y - fdf->map_height / 2) * 10;
	point->dz = point->raw_z;
	point->dx = tmp_x * cos(fdf->camera.r_xy) - tmp_y * sin(fdf->camera.r_xy);
	point->dy = tmp_x * sin(fdf->camera.r_xy) + tmp_y * cos(fdf->camera.r_xy);
	point->dx *= fdf->camera.magnify_x;
	point->dy *= fdf->camera.magnify_y;
	point->dz *= fdf->camera.magnify_z;
	point->dy -= point->dz;
	point->dx += fdf->camera.parallel_x;
	point->dy += fdf->camera.parallel_y;
	(void)tmp_z;
}

void	draw_line(t_fdf *fdf, t_data *data, t_point start, t_point end)
{
	t_point	dest;
	long	step_i;
	long	step_total;

	add_camera_effect(fdf, &start);
	add_camera_effect(fdf, &end);
	step_total = (fabs(start.dx - end.dx) + fabs(start.dy - end.dy)) / 2;
	step_i = 0;
	while (step_i <= step_total)
	{
		dest = mix_point(start, end, step_i, step_total);
		draw_pixel(data, lround(dest.dx), lround(dest.dy), dest.color);
		step_i++;
	}
}
