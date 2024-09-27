/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:13:14 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/27 13:41:45 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_player(int c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	is_valid_row(char *line)
{
	int	index;

	index = 0;
	while (line[index] != '\n' && line[index] != '\0')
	{
		if (is_player(line[index]) == false
			&& line[index] != MAP_DOOR
			&& line[index] != MAP_PATH
			&& line[index] != MAP_SPACE
			&& line[index] != MAP_WALL)
			return (false);
		index++;
	}
	return (true);
}

static bool	has_one_player(t_map *map)
{
	int		row;
	int		col;
	bool	player;

	row = 0;
	player = false;
	while (map->grid[row])
	{
		col = 0;
		while (map->grid[row][col])
		{
			if (player && is_player(map->grid[row][col]))
				return (false);
			if (is_player(map->grid[row][col]))
				player = true;
			col++;
		}
		row++;
	}
	return (player);
}

int	validate_map(t_map *map)
{
	if (is_enclosed(map)
		&& has_one_player(map)
		&& door_check(map))
		return (0);
	return (1);
}
