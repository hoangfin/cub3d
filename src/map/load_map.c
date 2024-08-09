/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:32:55 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/09 10:40:12 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	process_contents(t_map *specs, int fd)
{
	char	*data;
	int		status;

	status = get_next_line(fd, &data);
	while (status > -1)
	{
		if (ft_strcmp(data, "\n") != 0 && !ft_has_spaces_only_cubed(data))
		{
			if (extract_data(specs, data) > 0)
			{
				delete_map(specs, data);
				return (1);
			}
		}
		free(data);
		status = get_next_line(fd, &data);
	}
	return (0);
}

t_map	*load_map(const char *map_file)
{
	int	fd;
	t_map	map_specs;

	fd = open_file(map_file);
	if (fd < 0)
		return (NULL);
	map_specs = (t_map){};
	if (process_contents(map_specs, fd) > 0)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map_specs);
}

