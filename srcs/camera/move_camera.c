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

static void	move_camera_set(t_fdf *fdf, int key, double *x_val, double *y_val)
{
	if (key == W_KEYCODE)
	{
		*x_val = MOVE_RATE * fdf->camera.r_xy_sin;
		*y_val = MOVE_RATE * fdf->camera.r_xy_cos;
	}
	else if (key == S_KEYCODE)
	{
		*x_val = -MOVE_RATE * fdf->camera.r_xy_sin;
		*y_val = -MOVE_RATE * fdf->camera.r_xy_cos;
	}
	else if (key == A_KEYCODE)
	{
		*x_val = MOVE_RATE * fdf->camera.r_xy_cos;
		*y_val = -MOVE_RATE * fdf->camera.r_xy_sin;
	}
	else if (key == D_KEYCODE)
	{
		*x_val = -MOVE_RATE * fdf->camera.r_xy_cos;
		*y_val = MOVE_RATE * fdf->camera.r_xy_sin;
	}
}

void	move_camera(t_fdf *fdf, int move_key)
{
	double	x_val;
	double	y_val;

	x_val = 0;
	y_val = 0;
	move_camera_set(fdf, move_key, &x_val, &y_val);
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
