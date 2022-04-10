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

static int	round_inf(double val, int nearly_inf)
{
	int	class;

	class = fpclassify(val);
	if (class != FP_INFINITE && class != FP_NAN)
		return (lround(val));
	else
		return (lround(copysign(nearly_inf, val)));
}

static int	check_void(t_point start, t_point end)
{
	int	start_rounded_x;
	int	start_rounded_y;
	int	end_rounded_x;
	int	end_rounded_y;

	start_rounded_x = round_inf(start.dx, WIDTH + 100);
	start_rounded_y = round_inf(start.dy, HEIGHT + 100);
	end_rounded_x = round_inf(end.dx, WIDTH + 100);
	end_rounded_y = round_inf(end.dy, HEIGHT + 100);
	if (start_rounded_x < 0 && end_rounded_x < 0)
		return (1);
	if (start_rounded_x >= WIDTH && end_rounded_x >= WIDTH)
		return (1);
	if (start_rounded_y < 0 && end_rounded_y < 0)
		return (1);
	if (start_rounded_y >= HEIGHT && end_rounded_y >= HEIGHT)
		return (1);
	return (0);
}

static long	count_total_step(t_point start, t_point end)
{
	long	x_abs;
	long	y_abs;

	x_abs = lround(start.dx) - lround(end.dx);
	if (x_abs < 0)
		x_abs = -x_abs;
	y_abs = lround(start.dy) - lround(end.dy);
	if (y_abs < 0)
		y_abs = -y_abs;
	if (x_abs > y_abs)
		return (x_abs);
	else
		return (y_abs);
}

static t_point	mix_point(t_point start, t_point end, double rate)
{
	t_point	dest;

	if (rate <= 0)
		return (start);
	if (rate >= 1)
		return (end);
	dest.dx = start.dx * (1 - rate) + end.dx * rate;
	dest.dy = start.dy * (1 - rate) + end.dy * rate;
	dest.color = mix_color(start.color, end.color, rate);
	return (dest);
}

void	draw_line(t_fdf *fdf, t_data *data, t_point start, t_point end)
{
	t_point	dest;
	long	step_i;
	long	step_total;

	add_camera_effect(fdf, &start);
	add_camera_effect(fdf, &end);
	if (check_void(start, end))
		return ;
	step_total = count_total_step(start, end);
	step_i = 0;
	while (step_i <= step_total)
	{
		dest = mix_point(start, end, (double)step_i / (double)step_total);
		draw_pixel(data, round_inf(dest.dx, WIDTH + 100), \
			round_inf(dest.dy, HEIGHT + 100), dest.color);
		step_i++;
	}
}
