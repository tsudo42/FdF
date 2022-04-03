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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_point	mix_point(t_point start, t_point end, long step_i, long step_total)
{
	t_point	dest;
	long	color[4];
	long	color_tmp;
	int		i;

	dest.x = start.x + (end.x - start.x) * step_i / step_total;
	dest.y = start.y + (end.y - start.y) * step_i / step_total;
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
	dest.color = create_trgb(color[0], color[1], color[2], color[3]);
	return (dest);
}

void	draw_line(t_data *data, t_point start, t_point end, int color)
{
	t_point	dest;
	long	step_i;
	long	step_total;

	step_total = 0;
	if (end.x > start.x)
		step_total += end.x - start.x;
	else
		step_total += start.x - end.x;
	if (end.y > start.y)
		step_total += end.y - start.y;
	else
		step_total += start.y - end.y;
	step_i = 0;
	while (step_i <= step_total)
	{
		dest = mix_point(start, end, step_i, step_total);
		if (0 <= dest.x && dest.x < WIDTH && 0 <= dest.y && dest.y < HEIGHT)
			draw_pixel(data, dest.x, dest.y, dest.color);
		step_i++;
	}
	(void)color;
}
