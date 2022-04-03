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

void	my_draw_line(t_data *img)
{
	t_point	start;
	t_point	end;

	start.x = 10;
	start.y = 10;
	end.x = WIDTH - 10;
	end.y = HEIGHT - 10;
	draw_line(img, start, end, 0x00FF0000);
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
	my_draw_line(&fdf.img);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img, 0, 0);
	mlx_hook(fdf.win, 2, 0, key_hook, &fdf);
	mlx_hook(fdf.win, 17, 0, my_close, &fdf);
	mlx_loop(fdf.mlx);
}
