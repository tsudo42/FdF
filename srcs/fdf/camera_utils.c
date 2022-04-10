/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	reset_camera(t_fdf *fdf)
{
	fdf->camera.parallel_x = 0;
	fdf->camera.parallel_y = 0;
	fdf->camera.magnify_rate = 1;
	fdf->camera.r_xy = M_PI_4;
	return (0);
}

void	rotate_camera(t_fdf *fdf, int direction_key)
{
	if (direction_key == H_KEYCODE)
		fdf->camera.r_xy += M_PI_4 / 4;
	else if (direction_key == L_KEYCODE)
		fdf->camera.r_xy -= M_PI_4 / 4;
	if (fdf->camera.r_xy > M_PI)
		fdf->camera.r_xy -= M_PI * 2;
	else if (fdf->camera.r_xy < -M_PI)
		fdf->camera.r_xy += M_PI * 2;
}

void	move_camera(t_fdf *fdf, int move_key)
{
	if (move_key == W_KEYCODE)
	{
		fdf->camera.parallel_x += MOVE_RATE * sin(fdf->camera.r_xy);
		fdf->camera.parallel_y += MOVE_RATE * cos(fdf->camera.r_xy);
	}
	else if (move_key == S_KEYCODE)
	{
		fdf->camera.parallel_x -= MOVE_RATE * sin(fdf->camera.r_xy);
		fdf->camera.parallel_y -= MOVE_RATE * cos(fdf->camera.r_xy);
	}
	else if (move_key == A_KEYCODE)
	{
		fdf->camera.parallel_x += MOVE_RATE * cos(fdf->camera.r_xy);
		fdf->camera.parallel_y -= MOVE_RATE * sin(fdf->camera.r_xy);
	}
	else if (move_key == D_KEYCODE)
	{
		fdf->camera.parallel_x -= MOVE_RATE * cos(fdf->camera.r_xy);
		fdf->camera.parallel_y += MOVE_RATE * sin(fdf->camera.r_xy);
	}
}

void	zoom_camera(t_fdf *fdf, int zoomrate_key)
{
	if (zoomrate_key == J_KEYCODE)
	{
		if (fdf->camera.magnify_rate < MIN_ZOOM_RATE)
			return ;
		fdf->camera.magnify_rate /= ZOOM_RATE;
	}
	else if (zoomrate_key == K_KEYCODE)
	{
		if (fdf->camera.magnify_rate > MAX_ZOOM_RATE)
			return ;
		fdf->camera.magnify_rate *= ZOOM_RATE;
	}
}

void	add_camera_effect(t_fdf *fdf, t_point *point)
{
	double	tmp_x;
	double	tmp_y;

	point->dx = (point->raw_x - fdf->map_width / 2) * MAP_POSITION_ZOOM_RATE;
	point->dy = (point->raw_y - fdf->map_height / 2) * MAP_POSITION_ZOOM_RATE;
	point->dz = point->raw_z;
	point->dx += fdf->camera.parallel_x;
	point->dy += fdf->camera.parallel_y;
	point->dx *= fdf->camera.magnify_rate;
	point->dy *= fdf->camera.magnify_rate;
	point->dz *= fdf->camera.magnify_rate;
	tmp_x = \
		point->dx * cos(fdf->camera.r_xy) - point->dy * sin(fdf->camera.r_xy);
	tmp_y = \
		point->dx * sin(fdf->camera.r_xy) + point->dy * cos(fdf->camera.r_xy);
	point->dx = tmp_x;
	point->dy = tmp_y;
	point->dy -= point->dz;
	point->dy *= M_SQRT1_2;
	point->dx += WIDTH / 2;
	point->dy += HEIGHT / 2;
}
