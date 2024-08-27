/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:24:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/27 09:50:47 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	verify_texture(char *texture, int *error)
{
	int	fd;

	if (texture[0] == '\0' || verify_fileformat(texture, ".xpm") != 0) // change back to png!
	{
		*error = 1;
		write(STDERR_FILENO, "Error\nInvalid texture\n", 23);
		return (-1);
	}
	fd = check_file_permissions(texture);
	if (fd < 0)
	{
		*error = 1;
		return (-1);
	}
	close(fd);
	return (0);
}

static int	save_texture(t_map *map, char *line, int identifier, int *error)
{
	char	set[2];
	int		index;

	set[0] = '\n';
	set[1] = ' ';
	index = 0;
	while (index < 4)
	{
		if (identifier == index + 1)
		{
			map->wall_paths[index] = ft_strtrim(line + 2, set);
			if (!map->wall_paths[index])
			{
				*error = 1;
				write(STDERR_FILENO, "Error\nft_strtrim\n", 17);
				return (1);
			}
			if (verify_texture(map->wall_paths[index], error) < 0)
				return (1);
			return (0);
		}
		index++;
	}
	return (0);
}

static int	extract_texture(t_map *map, char *line, int identifier, int *error)
{
	if ((identifier == 1 && map->wall_paths[0])
		|| (identifier == 2 && map->wall_paths[1])
		|| (identifier == 3 && map->wall_paths[2])
		|| (identifier == 4 && map->wall_paths[3]))
		return (print_content_error(NULL, error));
	return (save_texture(map, line, identifier, error));
}

int	get_texture(t_map *map, char *data, int *error)
{
	char	*content;

	content = data;
	content = ft_strnstr(content, "NO", 2);
	if (content)
		return (extract_texture(map, content, 1, error));
	content = data;
	content = ft_strnstr(content, "EA", 2);
	if (content)
		return (extract_texture(map, content, 2, error));
	content = data;
	content = ft_strnstr(content, "SO", 2);
	if (content)
		return (extract_texture(map, content, 3, error));
	content = data;
	content = ft_strnstr(content, "WE", 2);
	if (content)
		return (extract_texture(map, content, 4, error));
	return (0);
}
