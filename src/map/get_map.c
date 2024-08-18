/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:26:40 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/18 15:04:29 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_map_size(t_map *map, char *data, int fd)
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

static void	copy_line(t_map *map, char *line, unsigned int index)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i] && line[i] != '\n')
		{
			map->grid[index][i] = line[i];
			i++;
		}
		map->grid[index][i] = '\0';
	}
}

static int	save_grid(t_map *map, int fd, char *data)
{
	char	*line;
	int		status;
	unsigned int		index;
	
	map->grid = (char **)malloc(sizeof(char *) * map->row_count + 1);
	if (!map->grid)
		return (1);
	index = 0;
	map->grid[index] = (char *)malloc(sizeof(char) * map->col_count + 2);
	if (!map->grid[index])
		return (1);
	copy_line(map, data, index);
	index++;
	status = get_next_line(fd, &line);
	while (status > -1 && line && index < map->row_count)
	{
		map->grid[index] = (char *)malloc(sizeof(char) * map->col_count + 2);
		if (!map->grid[index])
		{
			free(line);
			return (1);
		}
		copy_line(map, line, index);
		free(line);
		status = get_next_line(fd, &line);
		index++;
	}
	free(line);
	map->grid[index] = NULL;
	return (0);
}

int	get_map(t_map *map, char *data, int fd, char *pathname)
{
	int		second_read;
	int		status;
	char	*line;

	if (get_map_size(map, data, fd) > 0)
		return (1);
	second_read = check_file_permissions(pathname);
	if (second_read < 0)
		return (1);
	status = get_next_line(second_read, &line);
	while (status > -1 && line)
	{
		if (ft_strcmp(line, data) == 0)
		{
			if (save_grid(map, second_read, data) > 0)
			{
				close(second_read);
				return (1);
			}
			close(second_read);
			return (0);
		}
		free(line);
		status = get_next_line(second_read, &line);
	}
	free(line);
	close(second_read);
	return (0);
}