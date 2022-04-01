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

void	draw_line(t_data *data, t_point start, t_point end, int color)
{
	t_point	diff;
	long	i;
	long	pix_len;

	diff.x = end.x - start.x;
	diff.y = end.y - start.y;
	pix_len = diff.x * diff.x + diff.y * diff.y;
	i = 0;
	while (i < pix_len)
	{
		draw_pixel(data, start.x + i * diff.x / pix_len,
			start.y + i * diff.y / pix_len, color);
		i++;
	}
}
