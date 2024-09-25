/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:13:14 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/25 15:34:47 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_player(int c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
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

static bool	has_valid_chars(t_map *map)
{
	int		row;
	int		col;

	row = 0;
	while (map->grid[row])
	{
		col = 0;
		while (map->grid[row][col])
		{
			if (is_player(map->grid[row][col]) == false
				&& map->grid[row][col] != MAP_DOOR
				&& map->grid[row][col] != MAP_FOE
				&& map->grid[row][col] != MAP_PATH
				&& map->grid[row][col] != MAP_SPACE
				&& map->grid[row][col] != MAP_WALL)
				return (false);
			col++;
		}
		row++;
	}
	return (true);
}

int	validate_map(t_map *map)
{
	if (has_valid_chars(map)
		&& is_enclosed(map)
		&& has_one_player(map)
		&& door_check(map))
		return (0);
	return (1);
}
