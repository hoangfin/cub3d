/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_door.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:54:10 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/29 13:11:48 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_door(int32_t x, int32_t y, t_cub3D *cub3d)
{
	int32_t	row;
	int32_t	col;

	if (x < 0 || (uint32_t)x >= cub3d->map->width)
		return (false);
	if (y < 0 || (uint32_t)y >= cub3d->map->height)
		return (false);
	row = y / MAP_CELL_SIZE;
	col = x / MAP_CELL_SIZE;
	if (cub3d->map->grid[row][col] == MAP_DOOR)
		return (true);
	return (false);
}
