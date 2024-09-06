/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 21:39:22 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/05 23:29:51 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_wall(int32_t x, int32_t y, t_cub3D *cub3d)
{
	int32_t	row;
	int32_t	col;

	if (x < 0 || (uint32_t)x >= cub3d->map->width)
		return (false);
	if (y < 0 || (uint32_t)y >= cub3d->map->height)
		return (false);
	row = y / MAP_CELL_SIZE;
	col = x / MAP_CELL_SIZE;
	if (cub3d->map->grid[row][col] == MAP_WALL)
		return (true);
	return (false);
}