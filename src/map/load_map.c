/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:55 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/27 16:29:42 by hoatran          ###   ########.fr       */
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

static bool	has_all_walls(t_map *map)
{
	if (map->wall_paths[0]
		&& map->wall_paths[1]
		&& map->wall_paths[2]
		&& map->wall_paths[3]
	)
		return (true);
	return (false);
}

static char	*collect_world_info(t_map *map, int fd, int *error)
{
	char	*line;
	int		status;
	int		color_status;

	color_status = 0;
	status = get_next_line(fd, &line);
	while (status > -1 && line)
	{
		if (ft_strcmp(line, "\n") != 0 && !*error)
		{
			if (map_edge(line) == 0)
				break ;
			if (get_texture(map, line, error) == 2
				&& get_color(map, line, error, &color_status) == 2)
				print_content_error(NULL, error);
		}
		free(line);
		status = get_next_line(fd, &line);
	}
	if (color_status >= 2 && has_all_walls(map) && !*error)
		return (line);
	free(line);
	check_file_end(fd);
	return (NULL);
}

static int	process_mapfile(t_map *map, int fd, char *pathname)
{
	char	*first_map_row;
	int		error;

	error = 0;
	first_map_row = collect_world_info(map, fd, &error);
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
