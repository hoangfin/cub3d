/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_character_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:32:20 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/29 18:54:08 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_valid_position(int32_t x, int32_t y, t_cub3D *cub3D)
{
	int32_t	row;
	int32_t	col;

	row = y / MAP_CELL_SIZE;
	col = x / MAP_CELL_SIZE;
	if (cub3D->map->grid[row][col] == MAP_WALL)
		return (false);
	if (
		cub3D->map->grid[row][col + 1] == MAP_WALL
		&& x + MAP_PLAYER_SIZE >= (col + 1) * MAP_CELL_SIZE
	)
		return (false);
	if (
		cub3D->map->grid[row + 1][col + 1] == MAP_WALL
		&& x + MAP_PLAYER_SIZE >= (col + 1) * MAP_CELL_SIZE
		&& y + MAP_PLAYER_SIZE >= (row + 1) * MAP_CELL_SIZE
	)
		return (false);
	if (
		cub3D->map->grid[row + 1][col] == MAP_WALL
		&& y + MAP_PLAYER_SIZE >= (row + 1) * MAP_CELL_SIZE
	)
		return (false);
	return (true);
}

void	set_character_pos(double x, double y, t_cub3D *cub3D)
{
	if ((int32_t)x < 0 || (uint32_t)x + MAP_PLAYER_SIZE > cub3D->map->width)
		return ;
	if ((int32_t)y < 0 || (uint32_t)y + MAP_PLAYER_SIZE > cub3D->map->height)
		return ;
	if (!is_valid_position(x, y, cub3D))
		return ;
	cub3D->player.x = x;
	cub3D->player.y = y;
}
