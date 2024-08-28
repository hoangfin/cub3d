/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:01:10 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/28 10:29:32 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_bool	ft_has_spaces_only_cubed(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
	{
		if (!ft_isspace(str[i]))
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

t_bool	too_many_commas(char *str)
{
	int	index;
	int	commas;

	index = 0;
	commas = 0;
	while (str[index])
	{
		if (str[index] == ',')
			commas++;
		index++;
	}
	if (commas != 2)
		return (true);
	return (false);
}
