/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:13:14 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/19 14:08:45 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_bool	is_player(int c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

static t_bool	has_one_player(t_map *map)
{
	int		row;
	int		col;
	t_bool	player;

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

static t_bool	has_valid_chars(t_map *map)
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

static	t_bool	door_check(t_map *map)
{
	unsigned int	row;
	unsigned int	col;

	row = 0;
	while (map->grid[row])
	{
		col = 0;
		while (map->grid[row][col])
		{
			if (col > 0 && col < map->col_count
				&& row > 0 && row < map->row_count
				&& map->grid[row][col] == MAP_DOOR)
			{
				if ((map->grid[row][col - 1] != MAP_WALL
					&& map->grid[row][col + 1] != MAP_WALL)
					|| (map->grid[row - 1][col] != MAP_WALL
					&& map->grid[row + 1][col] != MAP_WALL))
					return (false);
				map->door_count++;
			}
			col++;
		}
		row++;
	}
	printf("door count: %u\n", map->door_count);
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
