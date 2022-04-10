/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_camera.c                                     :+:      :+:    :+:   */
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
	fdf->camera.z_rate = 1;
	fdf->camera.magnify_rate = 1;
	fdf->camera.r_xy = M_PI_4;
	return (0);
}
