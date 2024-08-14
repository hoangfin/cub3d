/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:46:11 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/14 09:51:36 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	verify_texture(char *texture)
{
	int	fd;
	
	if (texture[0] == '\0' || verify_fileformat(texture, ".png") != 0)
	{
		free(texture);
		write(STDERR_FILENO, "Error\nInvalid texture file format\n", 34);
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

static int	save_texture(mlx_t *mlx, t_map *specs, char *texture, int identifier)
{
	mlx_texture_t	*txture;

	txture = mlx_load_png(texture);
	if (!txture)
		return (1);
	if (identifier == 1)
		specs->north_wall = mlx_texture_to_image(mlx, txture);
	else if (identifier == 2)
		specs->south_wall = mlx_texture_to_image(mlx, txture);
	else if (identifier == 3)
		specs->west_wall = mlx_texture_to_image(mlx, txture);
	else if (identifier == 4)
		specs->east_wall = mlx_texture_to_image(mlx, txture);
	mlx_delete_texture(txture);
	return (0);
}

static int	extract_texture(mlx_t *mlx, t_map *specs, char *line, int identifier)
{
	char	*texture;

	texture = ft_strtrim(line + 2, " "); // print error?
	if (!texture || verify_texture(texture) < 0)
		return (1);
	if (identifier == 1 && specs->north_wall
		|| identifier == 2 && specs->south_wall
		|| identifier == 3 && specs->west_wall
		|| identifier == 4 && specs->east_wall)
		return (print_content_error(texture));
	if (save_texture(mlx, specs, texture, identifier) > 0)
	{
		free(texture);
		return (1);
	}
	free(texture);
	return (0);
}

static int	get_texture(mlx_t *mlx, t_map *specs, char *data)
{
	char	*content;
	
	content = data;
	if (ft_strnstr(content, "NO", 2))
		return (extract_texture(mlx, specs, content, 1));
	content = data;
	if (ft_strnstr(content, "SO", 2))
		return (extract_texture(mlx, specs, content, 2));
	content = data;
	if (ft_strnstr(content, "WE", 2))
		return (extract_texture(mlx, specs, content, 3));
	content = data;
	if (ft_strnstr(content, "EA", 2))
		return (extract_texture(mlx, specs, content, 4));
	return (0);
}

// how to differentiate return values for: A) faulty file content (free and exit), B) data processing failure (free and exit), C) didn't find what I was looking for & D) succesfully extracted data
int	extract_data(mlx_t *mlx, t_map *specs, char *data)
{
	if (get_texture(mlx, specs, data) > 0)
		return (1);
	if (get_color(specs, data) > 0)
		return (1);
	if (get_map(specs, data) > 0)
		return (1);
	return (0);
}
