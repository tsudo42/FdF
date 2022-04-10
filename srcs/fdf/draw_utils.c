/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_screen(t_fdf *fdf)
{
	ft_memset(fdf->img.addr, 0, fdf->img.line_length * HEIGHT);
}

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

void	draw_minimap(t_fdf *fdf)
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
