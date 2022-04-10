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

static void	toggle_minimap(t_fdf *fdf)
{
	if (fdf->camera.minimap)
		fdf->camera.minimap = 0;
	else
		fdf->camera.minimap = 1;
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == ESC_1_KEYCODE || keycode == ESC_2_KEYCODE)
		fdf_close(fdf);
	else if (keycode == P_KEYCODE)
		swap_color(fdf);
	else if (keycode == SPACE_KEYCODE)
		reset_camera(fdf);
	else if (keycode == H_KEYCODE || keycode == L_KEYCODE)
		rotate_camera(fdf, keycode);
	else if (keycode == W_KEYCODE || keycode == S_KEYCODE)
		move_camera(fdf, keycode);
	else if (keycode == A_KEYCODE || keycode == D_KEYCODE)
		move_camera(fdf, keycode);
	else if (keycode == J_KEYCODE || keycode == K_KEYCODE)
		zoom_camera(fdf, keycode);
	else if (keycode == M_KEYCODE)
		toggle_minimap(fdf);
	return (0);
}
