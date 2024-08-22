/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:26:40 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/22 09:27:30 by emansoor         ###   ########.fr       */
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

static int	save_row(t_map *map, char *line, unsigned int index)
{
	map->grid[index] = (char *)malloc(sizeof(char) * (map->col_count + 2));
	if (!map->grid[index])
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		if (index > 0)
			free(line);
		return (1);
	}
	copy_line(map, line, index);
	if (index > 0)
		free(line);
	return (0);
}

static int	save_grid(t_map *map, int fd, char *data)
{
	char				*line;
	int					status;
	unsigned int		index;

	map->grid = (char **)malloc(sizeof(char *) * (map->row_count + 1));
	if (!map->grid)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		return (1);
	}
	index = 0;
	if (save_row(map, data, index) > 0)
		return (1);
	index++;
	status = get_next_line(fd, &line);
	while (status > -1 && line && index < map->row_count)
	{
		if (save_row(map, line, index) > 0)
			return (1);
		status = get_next_line(fd, &line);
		index++;
	}
	free(line);
	map->grid[index] = NULL;
	return (0);
}

static int	find_grid_start(t_map *map, int fd, char *data)
{
	int		status;
	char	*line;

	status = get_next_line(fd, &line);
	while (status > -1 && line)
	{
		if (ft_strcmp(line, data) == 0)
		{
			if (save_grid(map, fd, data) > 0)
			{
				free(line);
				return (1);
			}
			free(line);
			return (0);
		}
		free(line);
		status = get_next_line(fd, &line);
	}
	free(line);
	return (0);
}

int	get_map(t_map *map, char *data, int fd, char *pathname)
{
	int		second_read;
	int		grid_status;

	if (get_map_size(map, data, fd) > 0)
		return (1);
	second_read = open(pathname, O_RDONLY, 0666);
	if (second_read < 0)
		return (1);
	grid_status = find_grid_start(map, second_read, data);
	close(second_read);
	return (grid_status);
}
