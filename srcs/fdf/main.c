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

int	fdf_close(t_fdf *fdf)
{
	int	i;

	mlx_destroy_image(fdf->mlx, fdf->img.img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	ft_free_set(&fdf->mlx, NULL);
	i = 0;
	while (i < fdf->map_height)
	{
		ft_free_set((void **)&(fdf->map[i]), NULL);
		i++;
	}
	ft_free_set((void **)&(fdf->map), NULL);
	exit(0);
}

int	update_fdf(t_fdf *fdf)
{
	draw_fdf(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img.img, 0, 0);
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
	mlx_key_hook(fdf.win, key_hook, &fdf);
	mlx_hook(fdf.win, 17, 0, fdf_close, &fdf);
	mlx_loop_hook(fdf.mlx, update_fdf, &fdf);
	mlx_loop(fdf.mlx);
}
