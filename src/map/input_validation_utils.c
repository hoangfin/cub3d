/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:01:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/27 16:31:22 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	has_spaces_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] != MAP_SPACE)
			return (false);
		i++;
	}
	return (true);
}

int	print_content_error(void *str, int *error)
{
	if (str)
		free(str);
	if (error)
		*error = 1;
	write(STDERR_FILENO, "Error\nInvalid map file contents\n", 32);
	return (1);
}

void	copy_line(t_map *map, char *line, unsigned int row)
{
	uint32_t	index;

	index = 0;
	if (line)
	{
		while (line[index] && line[index] != '\n' && index < map->col_count)
		{
			map->grid[row][index] = line[index];
			index++;
		}
		while (index < map->col_count)
		{
			map->grid[row][index] = MAP_SPACE;
			index++;
		}
		map->grid[row][index] = '\0';
	}
}

int	map_edge(char *line)
{
	int	index;

	index = 0;
	while (line[index] && line[index] != '\n')
	{
		if (line[index] != MAP_WALL && line[index] != MAP_SPACE)
			return (1);
		index++;
	}
	return (0);
}

bool	is_clean_texture(char *data, char *str)
{
	int	index;

	index = 0;
	if (data)
	{
		while (ft_strncmp(data + index, str, 2) != 0)
		{
			if (data[index] != MAP_SPACE)
				return (false);
			index++;
		}
		return (true);
	}
	return (false);
}
