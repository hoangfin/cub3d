/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:20:51 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/19 17:30:06 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_closed_door(int32_t row, int32_t col, t_cub3D *cub3d)
{
	uint32_t	i;

	i = 0;
	if (cub3d->map->grid[row][col] != MAP_DOOR)
		return (false);
	while (i < cub3d->map->door_count)
	{
		if (
			cub3d->doors[i].y / MAP_CELL_SIZE == row
			&& cub3d->doors[i].x / MAP_CELL_SIZE == col
			&& cub3d->doors[i].state == DOOR_CLOSED
		)
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid_position(int32_t x, int32_t y, t_cub3D *cub3d)
{
	int32_t	row;
	int32_t	col;

	if (
		x < 0 || (uint32_t)x >= cub3d->map->width
		|| y < 0 || (uint32_t)y >= cub3d->map->height
	)
		return (false);
	row = y / MAP_CELL_SIZE;
	col = x / MAP_CELL_SIZE;
	if (cub3d->map->grid[row][col] == MAP_WALL)
		return (false);
	if (is_closed_door(row, col, cub3d))
		return (false);
	return (true);
}
