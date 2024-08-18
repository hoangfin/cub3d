/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:55 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/18 14:50:38 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

static int	data_complete(t_map *specs)
{
	if (specs->wall_paths[0] && specs->wall_paths[1] && specs->wall_paths[2]
		&& specs->wall_paths[3] && specs->color_ceiling && specs->color_floor
		&& specs->grid)
		return (1);
	print_content_error(NULL, 5);
	return (0);
}

static int	process_contents(t_map *map, char *pathname, int fd)
{
	char	*data;
	int		status;

	status = get_next_line(fd, &data);
	while (status > -1 && data)
	{
		if (ft_strcmp(data, "\n") != 0 && !ft_has_spaces_only_cubed(data))
		{
			// add a check here when file contains additional data && data_complete > 0
			if (missing_map(map) > 0)
			{
				if (get_map(map, data, fd, pathname) > 0)
				{
					free(data);
					return (1);
				}
			}
			if (extract_data(map, data) > 0)
			{
				free(data);
				return (1);
			}
		}
		free(data);
		status = get_next_line(fd, &data);
	}
	free(data);
	if (data_complete(map) > 0)
		return (0);
	return (1);
}

t_map	*load_map(char *pathname)
{
	int		fd;
	t_map	*map;
	int		i;

	fd = validate(pathname);
	if (fd < 0)
		return (NULL);
	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (map == NULL || process_contents(map, pathname, fd) > 0)
	{
		close(fd);
		return (NULL);
	}
	if (close(fd) != 0)
		return (NULL);
	if (map->wall_paths[0])
		printf("north wall texture: %s\n", map->wall_paths[0]);
	if (map->wall_paths[1])
		printf("east wall texture: %s\n", map->wall_paths[1]);
	if (map->wall_paths[2])
		printf("south wall texture: %s\n", map->wall_paths[2]);
	if (map->wall_paths[3])
		printf("north wall texture: %s\n", map->wall_paths[3]);
	if (map->color_ceiling)
		printf("ceiling color: %u\n", map->color_ceiling);
	if (map->color_floor)
		printf("floor color: %u\n", map->color_floor);
	if (map->grid != NULL)
	{
		i = 0;
		while (map->grid[i])
		{
			printf("map->grid[%d] = %s\n", i, map->grid[i]);
			i++;
		}
	}
	return (map);
}

