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
	fdf->camera.parallel_x = WIDTH / 2;
	fdf->camera.parallel_y = HEIGHT / 2;
	fdf->camera.magnify_x = 4;
	fdf->camera.magnify_y = 3;
	fdf->camera.magnify_z = 3;
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

void	add_camera_effect(t_fdf *fdf, t_point *point)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_z;

	tmp_x = (point->raw_x - fdf->map_width / 2) * 10;
	tmp_y = (point->raw_y - fdf->map_height / 2) * 10;
	point->dz = point->raw_z;
	point->dx = tmp_x * cos(fdf->camera.r_xy) - tmp_y * sin(fdf->camera.r_xy);
	point->dy = tmp_x * sin(fdf->camera.r_xy) + tmp_y * cos(fdf->camera.r_xy);
	point->dx *= fdf->camera.magnify_x;
	point->dy *= fdf->camera.magnify_y;
	point->dz *= fdf->camera.magnify_z;
	point->dy -= point->dz;
	point->dx += fdf->camera.parallel_x;
	point->dy += fdf->camera.parallel_y;
	(void)tmp_z;
}
