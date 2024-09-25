/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:22 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 21:17:55 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_wall(int32_t x, int32_t y, t_map *map)
{
	int32_t	row;
	int32_t	col;

	if (x < 0 || (uint32_t)x >= map->width)
		return (false);
	if (y < 0 || (uint32_t)y >= map->height)
		return (false);
	row = y / MAP_CELL_SIZE;
	col = x / MAP_CELL_SIZE;
	if (map->grid[row][col] == MAP_WALL)
		return (true);
	return (false);
}
