/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	move_camera_set(t_fdf *fdf, double x_val, double y_val)
{
	if (fdf->camera.parallel_x > MAX_ZOOM_RATE && x_val > 0)
		return ;
	if (fdf->camera.parallel_y > MAX_ZOOM_RATE && y_val > 0)
		return ;
	if (fdf->camera.parallel_x < -MAX_ZOOM_RATE && x_val < 0)
		return ;
	if (fdf->camera.parallel_x < -MAX_ZOOM_RATE && y_val < 0)
		return ;
	fdf->camera.parallel_x += x_val;
	fdf->camera.parallel_y += y_val;
}

void	move_camera(t_fdf *fdf, int move_key)
{
	double	tmp_x;
	double	tmp_y;

	if (move_key == W_KEYCODE)
	{
		tmp_x = MOVE_RATE * sin(fdf->camera.r_xy);
		tmp_y = MOVE_RATE * cos(fdf->camera.r_xy);
	}
	else if (move_key == S_KEYCODE)
	{
		tmp_x = -MOVE_RATE * sin(fdf->camera.r_xy);
		tmp_y = -MOVE_RATE * cos(fdf->camera.r_xy);
	}
	else if (move_key == A_KEYCODE)
	{
		tmp_x = MOVE_RATE * cos(fdf->camera.r_xy);
		tmp_y = -MOVE_RATE * sin(fdf->camera.r_xy);
	}
	else if (move_key == D_KEYCODE)
	{
		tmp_x = -MOVE_RATE * cos(fdf->camera.r_xy);
		tmp_y = MOVE_RATE * sin(fdf->camera.r_xy);
	}
	move_camera_set(fdf, tmp_x, tmp_y);
}
