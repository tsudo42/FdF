/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	swap_color(t_fdf *fdf)
{
	int		x;
	int		y;
	int32_t	color_tmp;

	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			color_tmp = fdf->map[y][x].color;
			fdf->map[y][x].color = fdf->map[y][x].color_alt;
			fdf->map[y][x].color_alt = color_tmp;
			x++;
		}
		y++;
	}
}

int	key_hook(int keycode, t_fdf *fdf)
{
	ft_printf("keycode : %d\n", keycode);
	if (keycode == ESC_1_KEYCODE || keycode == ESC_2_KEYCODE)
		fdf_close(fdf);
	else if (keycode == P_KEYCODE)
		swap_color(fdf);
	return (0);
}
