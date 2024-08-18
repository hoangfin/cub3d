/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 09:24:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/18 12:25:20 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

static int	verify_texture(char *texture)
{
	int	fd;
	
	if (texture[0] == '\0' || verify_fileformat(texture, ".xpm") != 0) // change back to png!
	{
		free(texture);
		write(STDERR_FILENO, "Error\nInvalid texture\n", 23);
		return (-1);
	}
	fd = check_file_permissions(texture);
	if (fd < 0)
	{
		free(texture);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	save_texture(t_map *specs, char *texture, int identifier)
{
	if (identifier == 1)
		specs->wall_paths[0] = texture; // does this need strdup??
	else if (identifier == 2)
		specs->wall_paths[1] = texture;
	else if (identifier == 3)
		specs->wall_paths[2] = texture;
	else if (identifier == 4)
		specs->wall_paths[3] = texture;
	return (0);
}

static int	extract_texture(t_map *specs, char *line, int identifier)
{
	char	*texture;
	char	set[2];

	set[0] = '\n';
	set[1] = ' ';
	texture = ft_strtrim(line + 2, set);
	if (!texture || verify_texture(texture) < 0)
		return (1);
	if ((identifier == 1 && specs->wall_paths[0])
		|| (identifier == 2 && specs->wall_paths[1])
		|| (identifier == 3 && specs->wall_paths[2])
		|| (identifier == 4 && specs->wall_paths[3]))
		return (print_content_error(texture, 1));
	if (save_texture(specs, texture, identifier) > 0)
		return (1);
	return (0);
}

int	get_texture(t_map *specs, char *data)
{
	char	*content;

	content = data;
	if (ft_strnstr(content, "NO", 2))
		return (extract_texture(specs, content, 1));
	content = data;
	if (ft_strnstr(content, "EA", 2))
		return (extract_texture(specs, content, 2));
	content = data;
	if (ft_strnstr(content, "SO", 2))
		return (extract_texture(specs, content, 3));
	content = data;
	if (ft_strnstr(content, "WE", 2))
		return (extract_texture(specs, content, 4));
	return (0);
}
