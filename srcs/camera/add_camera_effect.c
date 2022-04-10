/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera_effect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_camera_effect(t_fdf *fdf, t_point *point)
{
	double	tmp_x;
	double	tmp_y;

	point->dx = (point->raw_x - fdf->map_width / 2) * 10;
	point->dy = (point->raw_y - fdf->map_height / 2) * 10;
	point->dx += fdf->camera.parallel_x;
	point->dy += fdf->camera.parallel_y;
	point->dx *= fdf->camera.magnify_rate;
	point->dy *= fdf->camera.magnify_rate;
	tmp_x = \
		point->dx * cos(fdf->camera.r_xy) - point->dy * sin(fdf->camera.r_xy);
	tmp_y = \
		point->dx * sin(fdf->camera.r_xy) + point->dy * cos(fdf->camera.r_xy);
	point->dx = tmp_x;
	point->dy = tmp_y;
	point->dy -= point->raw_z * \
		fdf->camera.magnify_rate * fdf->camera.z_rate / M_SQRT1_2;
	point->dy *= M_SQRT1_2;
	point->dx += WIDTH / 2;
	point->dy += HEIGHT / 2;
}
