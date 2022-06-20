/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dist_camera(t_fdf *fdf, int dist_key)
{
	if (dist_key == T_KEYCODE)
		fdf->camera.r_z += M_PI / 16;
	else if (dist_key == Y_KEYCODE)
		fdf->camera.r_z -= M_PI / 16;
	if (fdf->camera.r_z < 0)
		fdf->camera.r_z = 0;
	if (fdf->camera.r_z > M_PI_2)
		fdf->camera.r_z = M_PI_2;
	fdf->camera.r_z_cos = cos(fdf->camera.r_z);
}
