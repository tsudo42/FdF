/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_draw_line(t_fdf *fdf)
{
	int	x;
	int	y;

	ft_memset(fdf->img.addr, 0, fdf->img.line_length * fdf->map_height);
	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x + 1 < fdf->map_width)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y][x + 1]);
			if (y + 1 < fdf->map_height)
				draw_line(fdf, &(fdf->img), fdf->map[y][x], fdf->map[y + 1][x]);
			x++;
		}
		y++;
	}
}

int	my_close(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	ft_free_set(&fdf->mlx, NULL);
	ft_free_set((void **)&fdf->map, NULL);
	exit(0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	ft_printf("keycode : %d\n", keycode);
	if (keycode == ESC_1_KEYCODE || keycode == ESC_2_KEYCODE)
		my_close(fdf);
	return (0);
}

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

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	ft_memset(&fdf, 0, sizeof(t_fdf));
	if (argc != 2 || argv[1] == NULL)
		ft_exit(0, "input filename");
	load_file(&fdf, argv[1]);
	reset_camera(&fdf);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, WIDTH, HEIGHT, "fdf");
	fdf.img.img = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, \
			&fdf.img.bits_per_pixel, &fdf.img.line_length, &fdf.img.endian);
	my_draw_line(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img, 0, 0);
	mlx_hook(fdf.win, 2, 0, key_hook, &fdf);
	mlx_hook(fdf.win, 17, 0, my_close, &fdf);
	mlx_loop(fdf.mlx);
}
