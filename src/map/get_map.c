/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:26:40 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/19 14:04:50 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "cub3D.h"

static int	end_of_grid(char *line)
{
	int	index;

	while (line[index])
	{
		if (line[index] != MAP_WALL)
			return (1);
		index++;
	}
	return (0);
}

static int	get_map_size(t_map *map, char *data, int fd, t_bool *eof)
{
	int		line_count;
	int		status;
	char	*line;

	line_count = 1;
	map->col_count = ft_strlen(data) - 1;
	if (!map->col_count)
		return (1);
	status = get_next_line(fd, &line);
	while (status > -1 && line)
	{
		if (end_of_grid(line) > 0)
			*eof = true;
		if (ft_strcmp(line, "\n") != 0 && !ft_has_spaces_only_cubed(line))
			line_count++;
		free(line);
		status = get_next_line(fd, &line);
	}
	free(line);
	map->row_count = line_count;
	if (map->row_count < 2)
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
	char	*line;
	int		status;
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

static int	read_file(t_map *map, int fd, char *data)
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
	t_bool	eof;
	
	eof = false;
	if (get_map_size(map, data, fd, &eof) > 0)
		return (1);
	second_read = check_file_permissions(pathname);
	if (second_read < 0)
		return (1);
	grid_status = read_file(map, second_read, data);
	close(second_read);
	return (grid_status);
}
