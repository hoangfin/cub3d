/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:26:40 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/31 14:47:52 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "cub3D.h"

static int	get_map_size(t_map *map, char *data, int fd)
{
	int		status;
	char	*line;

	map->row_count = 1;
	map->col_count = ft_strlen(data) - 1;
	if (map->col_count < 3)
		return (1);
	status = get_next_line(fd, &line);
	while (status > -1 && line)
	{
		if (ft_strcmp(line, "\n") == 0 || ft_has_spaces_only_cubed(line))
			break ;
		else if (ft_strcmp(line, "\n") != 0 && !ft_has_spaces_only_cubed(line))
			map->row_count++;
		free(line);
		status = get_next_line(fd, &line);
	}
	free(line);
	if (map->row_count < 3 || check_file_end(fd) > 0)
		return (1);
	return (0);
}

static int	fill_grid(t_map *map, int fd, char *data)
{
	char			*line;
	int				status;
	unsigned int	row;
	int				error;

	error = 0;
	row = 0;
	copy_line(map, data, row);
	row++;
	status = get_next_line(fd, &line);
	while (status > -1 && line && row < map->row_count)
	{
		if (ft_strcmp(line, "\n") == 0 || ft_has_spaces_only_cubed(line))
			error = 1;
		copy_line(map, line, row);
		free(line);
		status = get_next_line(fd, &line);
		row++;
	}
	free(line);
	map->grid[row] = NULL;
	check_file_end(fd);
	if (status < 0 || error)
		return (1);
	return (0);
}

static int	allocate_grid(t_map *map)
{
	unsigned int	row;

	map->grid = (char **)malloc(sizeof(char *) * (map->row_count + 1));
	if (!map->grid)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		return (1);
	}
	row = 0;
	while (row < map->row_count)
	{
		map->grid[row] = (char *)malloc(sizeof(char) * (map->col_count + 1));
		if (!map->grid[row])
		{
			ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
			return (1);
		}
		row++;
	}
	return (0);
}

static int	get_grid(t_map *map, int fd, char *data)
{
	int		status;
	char	*line;

	status = get_next_line(fd, &line);
	while (status > -1 && line)
	{
		if (ft_strcmp(line, data) == 0)
			break ;
		free(line);
		status = get_next_line(fd, &line);
	}
	free(line);
	if (allocate_grid(map) > 0)
		return (1);
	return (fill_grid(map, fd, data));
}

int	get_map(t_map *map, char *data, int fd, char *pathname)
{
	int		second_read;
	int		grid_status;

	if (get_map_size(map, data, fd) > 0)
		return (1);
	map->width = map->col_count * MAP_CELL_SIZE;
	map->height = map->row_count * MAP_CELL_SIZE;
	second_read = open(pathname, O_RDONLY, 0666);
	if (second_read < 0)
		return (1);
	grid_status = get_grid(map, second_read, data);
	if (close(second_read) != 0)
		return (1);
	return (grid_status);
}
