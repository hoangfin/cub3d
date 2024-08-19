/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:55 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/19 14:08:20 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

static int	data_complete(t_map *map, char *data)
{
	if (
		map->wall_paths[0]
		&& map->wall_paths[1]
		&& map->wall_paths[2]
		&& map->wall_paths[3]
		&& map->color_ceiling
		&& map->color_floor
		&& map->grid
	)
		return (1);
	if (data == NULL)
		print_content_error(NULL, 5);
	return (0);
}

static int	save_file_contents(t_map *map, char *pathname, int fd, char *data)
{
	if (data_complete(map, data) > 0)
	{
		print_content_error(NULL, 6);
		return (1);
	}
	if (missing_map(map) > 0)
	{
		if (end_of_grid(data) > )
		if (get_map(map, data, fd, pathname) > 0)
			return (1);
	}
	if (extract_data(map, data) > 0)
		return (1);
	return (0);
}

static int	process_mapfile(t_map *map, char *pathname, int fd)
{
	char	*data;
	int		status;

	status = get_next_line(fd, &data);
	while (status > -1 && data)
	{
		if (ft_strcmp(data, "\n") != 0 && !ft_has_spaces_only_cubed(data))
		{
			if (save_file_contents(map, pathname, fd, data) > 0)
			{
				free(data);
				return (1);
			}
		}
		free(data);
		status = get_next_line(fd, &data);
	}
	free(data);
	if (data_complete(map, NULL) > 0)
		return (0);
	return (1);
}

t_map	*load_map(char *pathname)
{
	int		fd;
	t_map	*map;

	fd = validate(pathname);
	if (fd < 0)
		return (NULL);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (map == NULL || process_mapfile(map, pathname, fd) > 0)
	{
		delete_map(map);
		close(fd);
		return (NULL);
	}
	if (close(fd) != 0)
	{
		delete_map(map); 
		return (NULL);
	}	
	return (map);
}

