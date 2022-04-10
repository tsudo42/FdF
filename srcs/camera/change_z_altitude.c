/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_z_altitude.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_z_altitude_camera(t_fdf *fdf, int direction_key)
{
	int	is_up;

	if (direction_key == U_KEYCODE)
		is_up = 1;
	else if (direction_key == I_KEYCODE)
		is_up = 0;
	if (is_up)
	{
		if (fdf->camera.z_rate < 7)
			fdf->camera.z_rate *= 2;
		else if (fdf->camera.z_rate < 100)
			fdf->camera.z_rate *= 1.25;
	}
	else
	{
		if (fdf->camera.z_rate > 9)
			fdf->camera.z_rate /= 1.25;
		else if (fdf->camera.z_rate > 0.01)
			fdf->camera.z_rate /= 2;
	}
}
