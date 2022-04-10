/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_minimap(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	point;

	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			point = fdf->map[y][x];
			if (point.raw_x < fdf->map_width && point.raw_y < fdf->map_height)
				draw_pixel(&(fdf->img), point.raw_x, point.raw_y, point.color);
			x++;
		}
		y++;
	}
}

static void	draw_fdf_iter_x(t_fdf *fdf, int x, int y, int is_angle_positive)
{
	if (is_angle_positive)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x + 1 < fdf->map_width)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y][x + 1]);
			if (y + 1 < fdf->map_height)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y + 1][x]);
			x++;
		}
	}
	else
	{
		x = fdf->map_width - 1;
		while (x >= 0)
		{
			if (x + 1 < fdf->map_width)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y][x + 1]);
			if (y + 1 < fdf->map_height)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y + 1][x]);
			x--;
		}
	}
}

void	draw_fdf(t_fdf *fdf)
{
	int	y;
	int	is_angle_positive;

	reset_screen(fdf);
	is_angle_positive = fdf->camera.r_xy > 0;
	if (-M_2_PI < fdf->camera.r_xy && fdf->camera.r_xy < M_2_PI)
	{
		y = 0;
		while (y < fdf->map_height)
		{
			draw_fdf_iter_x(fdf, 0, y, is_angle_positive);
			y++;
		}
	}
	else
	{
		y = fdf->map_height - 1;
		while (y >= 0)
		{
			draw_fdf_iter_x(fdf, 0, y, is_angle_positive);
			y--;
		}
	}
	if (fdf->camera.minimap)
		draw_minimap(fdf);
}
