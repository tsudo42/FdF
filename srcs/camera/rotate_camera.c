/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	fdf->camera.r_xy_cos = cos(fdf->camera.r_xy);
	fdf->camera.r_xy_sin = sin(fdf->camera.r_xy);
}
