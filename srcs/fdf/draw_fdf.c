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

static void	draw_fdf_reverse_y(t_fdf *fdf)
{
	int	x;
	int	y;

	y = fdf->map_height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x + 1 < fdf->map_width)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y][x + 1]);
			if (y - 1 >= 0)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y - 1][x]);
			x++;
		}
		y--;
	}
}

static void	draw_fdf_reverse_x(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map_height)
	{
		x = fdf->map_width - 1;
		while (x >= 0)
		{
			if (x - 1 >= 0)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y][x - 1]);
			if (y + 1 < fdf->map_height)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y + 1][x]);
			x--;
		}
		y++;
	}
}

static void	draw_fdf_reverse_xy(t_fdf *fdf)
{
	int	x;
	int	y;

	y = fdf->map_height - 1;
	while (y >= 0)
	{
		x = fdf->map_width - 1;
		while (x >= 0)
		{
			if (x - 1 >= 0)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y][x - 1]);
			if (y - 1 >= 0)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y - 1][x]);
			x--;
		}
		y--;
	}
}

static void	draw_fdf_normal(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map_height)
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
		y++;
	}
}

void	draw_fdf(t_fdf *fdf)
{
	reset_screen(fdf);
	if (0 <= fdf->camera.r_xy && fdf->camera.r_xy < 1.5)
		draw_fdf_normal(fdf);
	else if (-1.5 < fdf->camera.r_xy && fdf->camera.r_xy < 0)
		draw_fdf_reverse_x(fdf);
	else if (fdf->camera.r_xy > 0)
		draw_fdf_reverse_y(fdf);
	else
		draw_fdf_reverse_xy(fdf);
	if (fdf->camera.minimap)
		draw_minimap(fdf);
}
