/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:08:15 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/19 15:17:09 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_bool	is_inside_grid(t_map *map, unsigned int row, unsigned int col)
{
	if (col > 0 && col < map->col_count && row > 0 && row < map->row_count
		&& map->grid[row][col] == MAP_DOOR)
		return (true);
	return (false);
}

static t_bool	valid_door(t_map *map, unsigned int row, unsigned int col)
{
	if ((map->grid[row][col - 1] == MAP_WALL
		&& map->grid[row][col + 1] == MAP_WALL)
		|| (map->grid[row - 1][col] == MAP_WALL
		&& map->grid[row + 1][col] == MAP_WALL))
		{
			if (map->grid[row][col - 1] != MAP_DOOR
				&& map->grid[row][col + 1] != MAP_DOOR
				&& map->grid[row - 1][col] != MAP_DOOR
				&& map->grid[row + 1][col] != MAP_DOOR)
					return (true);
		}
	return (false);
}

t_bool	door_check(t_map *map)
{
	unsigned int	row;
	unsigned int	col;

	row = 0;
	while (map->grid[row])
	{
		col = 0;
		while (map->grid[row][col])
		{
			if (is_inside_grid(map, row, col) == true)
			{
				if (valid_door(map, row, col) == true)
					map->door_count++;
				else
					return (false);
			}
			col++;
		}
		row++;
	}
	return (true);
}