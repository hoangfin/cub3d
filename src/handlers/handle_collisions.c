/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_collisions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:37:07 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 10:28:57 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	has_collision(int32_t x, int32_t y, t_cub3D *cub3d)
{
	if (
		!is_valid_position(x, y, cub3d)
		|| !is_valid_position(x + MAP_PLAYER_SIZE, y, cub3d)
		|| !is_valid_position(x, y + MAP_PLAYER_SIZE, cub3d)
		|| !is_valid_position(x + MAP_PLAYER_SIZE, y + MAP_PLAYER_SIZE, cub3d)
	)
		return (true);
	return (false);
}

static void	handle_wall_collision(t_cub3D *cub3d)
{
	t_character *const	player = &cub3d->player;
	const int32_t		row = player->y / MAP_CELL_SIZE;
	const int32_t		col = player->x / MAP_CELL_SIZE;

	if (has_collision(player->x, player->prev_y, cub3d))
	{
		if (player->prev_x > player->x)
			player->x = (col + 1) * MAP_CELL_SIZE;
		else if (player->prev_x < player->x)
			player->x = ((uint32_t)player->prev_x / MAP_CELL_SIZE + 1) * MAP_CELL_SIZE - 1 - MAP_PLAYER_SIZE;
	}

	if (has_collision(player->prev_x, player->y, cub3d))
	{
		if (player->prev_y > player->y)
			player->y = (row + 1) * MAP_CELL_SIZE;
		else if (player->prev_y < player->y)
			player->y = ((uint32_t)player->prev_y / MAP_CELL_SIZE + 1) * MAP_CELL_SIZE - 1 - MAP_PLAYER_SIZE;
	}

	if (has_collision(player->x, player->y, cub3d))
	{
		if (player->prev_x > player->x)
			player->x = (col + 1) * MAP_CELL_SIZE;
		else if (player->prev_x < player->x)
			player->x = ((uint32_t)player->prev_x / MAP_CELL_SIZE + 1) * MAP_CELL_SIZE - 1 - MAP_PLAYER_SIZE;
		if (player->prev_y > player->y)
			player->y = (row + 1) * MAP_CELL_SIZE;
		else if (player->prev_y < player->y)
			player->y = ((uint32_t)player->prev_y / MAP_CELL_SIZE + 1) * MAP_CELL_SIZE - 1 - MAP_PLAYER_SIZE;
	}
}

void	handle_collisions(t_cub3D *cub3d)
{
	handle_wall_collision(cub3d);
}
