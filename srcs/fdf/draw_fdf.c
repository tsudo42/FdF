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

void	draw_fdf(t_fdf *fdf)
{
	int	x;
	int	y;

	reset_screen(fdf);
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
