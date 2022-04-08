/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	load_z_point(char *z_str)
{
	long	z_value;
	char	*endptr;

	z_value = ft_strtol(z_str, &endptr, 0);
	if (z_value < INT_MIN / 100 || INT_MAX / 100 < z_value)
		ft_exit(1, "map error: too big");
	if (*endptr != '\0' && *endptr != '\n')
	{
		ft_putstr_fd("map error: invalid parameter: ", 2);
		ft_putendl_fd(z_str, 2);
		ft_exit(1, NULL);
	}
	return (z_value);
}

static int	load_color_value(char *color_str)
{
	char			*endptr;
	unsigned long	color_value;

	if (color_str != NULL)
	{
		color_value = ft_strtoul(color_str, &endptr, 0);
		if (UINT32_MAX < color_value || (*endptr != '\0' && *endptr != '\n'))
		{
			ft_putstr_fd("map error: invalid parameter: ", 2);
			ft_putendl_fd(color_str, 2);
			ft_exit(1, NULL);
		}
		return (color_value);
	}
	else
		return (create_trgb(0, 0xFF, 0xFF, 0xFF));
}

/* ************************************************************************** */
/*  token: "12345,12345" meaning <z potision>,<color value>.                  */
/* ************************************************************************** */
void	load_point(t_point *point, char *token, int x, int y)
{
	char			*color_str;

	color_str = ft_strchr(token, ',');
	if (color_str != NULL)
	{
		*color_str = '\0';
		color_str++;
	}
	point->x = x;
	point->y = y;
	point->z = load_z_point(token);
	point->color = load_color_value(color_str);
}
