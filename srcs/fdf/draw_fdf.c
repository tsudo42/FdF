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

static void	draw_fdf_inverse(t_fdf *fdf)
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

void	draw_fdf(t_fdf *fdf)
{
	int	x;
	int	y;

	reset_screen(fdf);
	if (fdf->camera.r_xy < -M_PI_4 || M_PI_2 + M_PI_4 < fdf->camera.r_xy)
	{
		draw_fdf_inverse(fdf);
		return ;
	}
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
