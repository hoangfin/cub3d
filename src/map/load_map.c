/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:55 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/27 14:05:19 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	data_complete(t_map *map)
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
	return (0);
}

static t_bool	has_all_walls(t_map *map)
{
	if (map->wall_paths[0]
		&& map->wall_paths[1]
		&& map->wall_paths[2]
		&& map->wall_paths[3]
	)
		return (true);
	return (false);
}

static char	*get_wall_specs(t_map *map, int fd, int *error)
{
	char	*data;
	int		status;
	int		colors;

	colors = 0;
	status = get_next_line(fd, &data);
	while (status > -1 && data)
	{
		if (ft_strcmp(data, "\n") != 0 && !ft_has_spaces_only_cubed(data))
		{
			if (map_edge(data) == 0)
				break ;
			get_texture(map, data, error);
			get_color(map, data, error, &colors);
		}
		free(data);
		status = get_next_line(fd, &data);
	}
	if (colors >= 2 && has_all_walls(map) && !*error)
		return (data);
	free(data);
	check_file_end(fd);
	return (NULL);
}

static int	process_mapfile(t_map *map, int fd, char *pathname)
{
	char	*first_map_row;
	int		error;

	error = 0;
	first_map_row = get_wall_specs(map, fd, &error);
	if (first_map_row)
	{
		if (get_map(map, first_map_row, fd, pathname) > 0)
		{
			return (print_content_error(first_map_row, NULL));
		}
		free(first_map_row);
		if (data_complete(map) > 0)
			return (0);
		return (print_content_error(NULL, NULL));
	}
	if (!error)
		return (print_content_error(NULL, NULL));
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
	if (map == NULL || process_mapfile(map, fd, pathname) > 0)
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
	if (validate_map(map) > 0)
	{
		print_content_error(NULL, NULL);
		delete_map(map);
		return (NULL);
	}
	return (map);
}
