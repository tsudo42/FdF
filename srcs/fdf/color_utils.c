/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	create_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int32_t	mix_color(int32_t start_color, int32_t end_color, double rate)
{
	long	color[4];
	long	color_tmp;
	int		i;

	if (rate <= 0)
		return (start_color);
	if (rate >= 1)
		return (end_color);
	i = 0;
	while (i < 4)
	{
		color[i] = ((start_color >> ((3 - i) * 8)) & 0xFF);
		color_tmp = ((end_color >> ((3 - i) * 8)) & 0xFF);
		color[i] = color[i] * rate + color_tmp * (1 - rate);
		if (color[i] < 0)
			color[i] = 0;
		if (color[i] > UINT8_MAX)
			color[i] = UINT8_MAX;
		i++;
	}
	return (create_trgb(color[0], color[1], color[2], color[3]));
}
