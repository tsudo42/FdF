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

/* ************************************************************************** */
/*  Closer to start, more proportion of start color.                          */
/* ************************************************************************** */
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
		color[i] = ((end_color >> ((3 - i) * 8)) & 0xFF);
		color_tmp = ((start_color >> ((3 - i) * 8)) & 0xFF);
		color[i] = color[i] * rate + color_tmp * (1 - rate);
		if (color[i] < 0)
			color[i] = 0;
		if (color[i] > UINT8_MAX)
			color[i] = UINT8_MAX;
		i++;
	}
	return (create_trgb(color[0], color[1], color[2], color[3]));
}

static void	set_altcolor_helper( \
	t_fdf *fdf, double max_z, double min_z, int32_t white)
{
	int				x;
	int				y;
	int				tmp_z;

	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			tmp_z = fdf->map[y][x].raw_z;
			if (tmp_z > 0)
				fdf->map[y][x].color_alt = mix_color(white, \
					create_trgb(0, 0xFF, 0, 0), tmp_z / max_z);
			else if (tmp_z < 0)
				fdf->map[y][x].color_alt = mix_color(white, \
					create_trgb(0, 0, 0, 0xFF), tmp_z / min_z);
			else
				fdf->map[y][x].color_alt = white;
			x++;
		}
		y++;
	}
}

void	set_altcolor(t_fdf *fdf)
{
	int	max_z;
	int	min_z;
	int	x;
	int	y;
	int	tmp_z;

	max_z = 0;
	min_z = 0;
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			tmp_z = fdf->map[y][x].raw_z;
			if (tmp_z > 0 && max_z < tmp_z)
				max_z = tmp_z;
			else if (tmp_z < 0 && min_z > tmp_z)
				min_z = tmp_z;
			x++;
		}
		y++;
	}
	set_altcolor_helper(fdf, max_z, min_z, create_trgb(0, 0xFF, 0xFF, 0xFF));
}
