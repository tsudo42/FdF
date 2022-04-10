/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/08 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
