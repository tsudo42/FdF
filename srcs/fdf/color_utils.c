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

int32_t	create_trgb(uint8_t t, uint8_t r, uint8_t g, uint8_t b)
{
	return (*(int32_t *)(uint8_t [4]){b, g, r, t});
}

uint8_t	get_t(int32_t trgb)
{
	return (((uint8_t *)&trgb)[3]);
}

uint8_t	get_r(int32_t trgb)
{
	return (((uint8_t *)&trgb)[2]);
}

uint8_t	get_g(int32_t trgb)
{
	return (((uint8_t *)&trgb)[1]);
}

uint8_t	get_b(int32_t trgb)
{
	return (((uint8_t *)&trgb)[0]);
}
