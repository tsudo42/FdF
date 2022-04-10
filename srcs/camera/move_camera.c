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
