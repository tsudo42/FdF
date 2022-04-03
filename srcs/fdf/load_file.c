/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 00:00:00 by tsudo             #+#    #+#             */
/*   Updated: 2022/04/01 00:00:00 by tsudo            ###   ##########        */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

void	ft_append_content(t_list **lst, void *content)
{
	t_list	*node;
	t_list	*back;
	size_t	size;

	node = ft_lstnew(content);
	if (node == NULL)
		ft_exit(1, "malloc error");
	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = node;
		return ;
	}
	size = 1;
	back = (*lst);
	while (back->next != NULL)
	{
		size++;
		back = back->next;
	}
	if (size > INT_MAX)
		ft_exit(1, "map error: too big");
	back->next = node;
}

void	interpret_map(t_list *map_list, t_point **point_table)
{
	t_list	*row_list;
	int		x;
	int		y;

	y = 0;
	while (map_list != NULL)
	{
		row_list = map_list->content;
		x = 0;
		while (row_list != NULL)
		{
			point_table[y][x].x = x;
			point_table[y][x].y = y;
			point_table[y][x].z = ft_atoi(row_list->content);
			point_table[y][x].color = create_trgb(0, 0xFF, 0, 0);
			x++;
			row_list = row_list->next;
		}
		ft_lstclear(&row_list, NULL);
		y++;
		map_list = map_list->next;
	}
	ft_lstclear(&map_list, NULL);
}

t_list	*read_map(int fd, t_list **to_free)
{
	t_list	*map_list;
	t_list	*row_list;
	char	*line;
	char	*token;

	map_list = NULL;
	row_list = NULL;
	*to_free = NULL;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_append_content(to_free, line);
		token = ft_strtok(line, " ");
		while (token != NULL)
		{
			ft_append_content(&row_list, token);
			token = ft_strtok(NULL, " ");
		}
		ft_append_content(&map_list, row_list);
		row_list = NULL;
		line = get_next_line(fd);
	}
	return (map_list);
}

t_point	**alloc_table(t_list *map_list, int height, int width)
{
	t_list	*row_list;
	t_point	**point_table;
	size_t	i;

	if (height <= 0 || width <= 0)
		ft_exit(1, "map error: blank line");
	if (height != ft_lstsize(map_list))
		ft_exit(1, "internal error");
	point_table = malloc(sizeof(t_point *) * height);
	if (point_table == NULL)
		ft_exit(1, "malloc error");
	i = 0;
	while (map_list != NULL)
	{
		row_list = map_list->content;
		if (width != ft_lstsize(row_list))
			ft_exit(1, "map error: inconsistent width");
		point_table[i] = malloc(sizeof(t_point) * width);
		if (point_table[i] == NULL)
			ft_exit(1, "malloc error");
		i++;
		map_list = map_list->next;
	}
	return (point_table);
}

void	load_file(t_fdf *fdf, const char *filename)
{
	int		fd;
	t_list	*map_list;
	t_list	*to_free;
	t_point	**point_table;

	if (filename == NULL)
		ft_exit(1, "filename error");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_exit(1, "open error");
	to_free = NULL;
	map_list = read_map(fd, &to_free);
	if (map_list == NULL)
		ft_exit(1, "map error");
	fdf->map_height = ft_lstsize(map_list);
	fdf->map_width = ft_lstsize(map_list->content);
	point_table = alloc_table(map_list, fdf->map_height, fdf->map_width);
	interpret_map(map_list, point_table);
	ft_lstclear(&to_free, free);
	fdf->map = point_table;
	if (close(fd) < 0)
		ft_exit(1, "close error");
}
