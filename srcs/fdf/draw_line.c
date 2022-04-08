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
	step_total = (fabs(start.dx - end.dx) + fabs(start.dy - end.dy)) / 2;
	step_i = 0;
	while (step_i <= step_total)
	{
		dest = mix_point(start, end, (double)step_i / (double)step_total);
		draw_pixel(data, lround(dest.dx), lround(dest.dy), dest.color);
		step_i++;
	}
}
