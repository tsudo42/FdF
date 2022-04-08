/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_void(t_point start, t_point end)
{
	if (start.raw_x < 0 && end.raw_x < 0)
		return (1);
	if (start.raw_y < 0 && end.raw_y < 0)
		return (1);
	if (start.raw_x >= WIDTH && end.raw_x >= WIDTH)
		return (1);
	if (start.raw_y >= HEIGHT && end.raw_y >= HEIGHT)
		return (1);
	return (0);
}

static long	count_total_step(t_point start, t_point end)
{
	long	x_abs;
	long	y_abs;

	x_abs = start.raw_x - end.raw_x;
	if (x_abs < 0)
		x_abs = -x_abs;
	y_abs = start.raw_y - end.raw_y;
	if (y_abs < 0)
		y_abs = -y_abs;
	if (x_abs > y_abs)
		return (x_abs);
	else
		return (y_abs);
}

static t_point	mix_point(t_point start, t_point end, double rate)
{
	if (rate <= 0)
		return (start);
	if (rate >= 1)
		return (end);
	start.dx = start.dx * (1 - rate) + end.dx * rate;
	start.dy = start.dy * (1 - rate) + end.dy * rate;
	start.color = mix_color(start.color, end.color, rate);
	return (start);
}

void	draw_line(t_fdf *fdf, t_data *data, t_point start, t_point end)
{
	t_point	dest;
	long	step_i;
	long	step_total;

	add_camera_effect(fdf, &start);
	add_camera_effect(fdf, &end);
	start.raw_x = lround(start.dx);
	start.raw_y = lround(start.dy);
	end.raw_x = lround(end.dx);
	end.raw_y = lround(end.dy);
	if (check_void(start, end))
		return ;
	step_total = count_total_step(start, end);
	step_i = 0;
	while (step_i <= step_total)
	{
		dest = mix_point(start, end, (double)step_i / (double)step_total);
		draw_pixel(data, lround(dest.dx), lround(dest.dy), dest.color);
		step_i++;
	}
}
