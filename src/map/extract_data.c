/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:46:11 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/09 12:56:48 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	verify_texture(char *texture)
{
	int	fd;
	
	if (verify_fileformat(texture, ".png") != 0)
	{
		free(texture);
		ft_putstr_fd("cub3d: ");
		ft_putstr_fd("Invalid texture format\n");
		return (1);
	}
	fd = open(texture, O_RDONLY, 0666);
	if (fd < 0)
	{
		perror("cub3d");
		free(texture);
		return (1);
	}
	close(fd);
	return (0);
}

static int	extract_texture(t_map *specs, char *line, int identifier)
{
	char	*texture;

	texture = ft_strtrim(line + 2, " ");
	if (!texture || verify_texture(texture) > 0) // print error?
		return (1);
	if (identifier == 1 && specs->no)
		return (print_content_error(texture));
	else if (identifier == 1 && !specs->no)
		specs->no = texture;
	else if (identifier == 2 && specs->so)
		return (print_content_error(texture));
	else if (identifier == 2 && !specs->so)
		specs->so = texture;
	else if (identifier == 3 && specs->we)
		return (print_content_error(texture));
	else if (identifier == 3 && !specs->we)
		specs->we = texture;
	else if (identifier == 4 && specs->ea)
		return (print_content_error(texture));
	else if (identifier == 4 && !specs->ea)
		specs->ea = texture;
	return (0);
}

static int	get_texture(t_map *specs, char *data)
{
	char	*content;
	
	content = data;
	if (ft_strnstr(content, "NO", 2))
		return (extract_texture(specs, content, 1));
	content = data;
	if (ft_strnstr(content, "SO", 2))
		return (extract_texture(specs, content, 2));
	content = data;
	if (ft_strnstr(content, "WE", 2))
		return (extract_texture(specs, content, 3));
	content = data;
	if (ft_strnstr(content, "EA", 2))
		return (extract_texture(specs, content, 4));
	return (0);
}

// how to differentiate return values for: A) faulty file content (free and exit), B) data processing failure (free and exit), C) didn't find what I was looking for & D) succesfully extracted data
int	extract_data(t_map *specs, char *data)
{
	if (get_texture(specs, data) > 0)
		return (1);
	if (get_color(specs, data) > 0)
		return (1);
	if (get_map(specs, data) > 0)
		return (1);
	return (0);
}
