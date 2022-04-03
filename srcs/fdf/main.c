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

void	connect_points(t_data *data, t_point start, t_point end)
{
	start.x *= 20;
	start.y *= 20;
	start.x += 100 - start.z * 1;
	start.y += 100 - start.z * 1;
	end.x *= 20;
	end.y *= 20;
	end.x += 100 - end.z * 1;
	end.y += 100 - end.z * 1;
	draw_line(data, start, end, 0x00FF0000);
}

void	my_draw_line(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map_height)
	{
		x = 0;
		while (x < fdf->map_width)
		{
			if (x + 1 < fdf->map_width)
				connect_points(&(fdf->img), fdf->map[y][x], fdf->map[y][x + 1]);
			if (y + 1 < fdf->map_height)
				connect_points(&(fdf->img), fdf->map[y][x], fdf->map[y + 1][x]);
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

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	ft_memset(&fdf, 0, sizeof(t_fdf));
	if (argc != 2 || argv[1] == NULL)
		ft_exit(0, "input filename");
	load_file(&fdf, argv[1]);
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
