/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_file_eof.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_empty_line(const char *line)
{
	while (ft_isspace(*line))
		line++;
	return (*line == '\0');
}

void	load_file_eof(int fd, const char *error_msg)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_empty_line(line))
			ft_exit(1, error_msg);
		ft_free_set((void **)&line, NULL);
		line = get_next_line(fd);
	}
}