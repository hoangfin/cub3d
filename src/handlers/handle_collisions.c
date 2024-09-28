/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_collisions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:37:07 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/28 21:26:33 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_collision(int32_t x, int32_t y, t_cub3D *cub3d)
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

static void	handle_x_collision(int32_t x, int32_t y, t_cub3D *cub3d)
{
	t_player *const	player = &cub3d->player;
	const int32_t	row = y / MAP_CELL_SIZE;
	const int32_t	col = x / MAP_CELL_SIZE;
	t_door			*door;

	if (player->prev_x > x)
	{
		player->x = (col + 1) * MAP_CELL_SIZE;
		door = get_door(row, col, cub3d);
	}
	else if (player->prev_x < x)
	{
		player->x = (col + 1) * MAP_CELL_SIZE - 1 - MAP_PLAYER_SIZE;
		door = get_door(row, col + 1, cub3d);
	}
	if (door != NULL)
		transition_door(door, DOOR_OPENING);
}

static void	handle_y_collision(int32_t x, int32_t y, t_cub3D *cub3d)
{
	t_player *const	player = &cub3d->player;
	const int32_t	row = y / MAP_CELL_SIZE;
	const int32_t	col = x / MAP_CELL_SIZE;
	t_door			*door;

	if (player->prev_y > player->y)
	{
		player->y = (row + 1) * MAP_CELL_SIZE;
		door = get_door(row, col, cub3d);
	}
	else if (player->prev_y < player->y)
	{
		player->y = (row + 1) * MAP_CELL_SIZE - 1 - MAP_PLAYER_SIZE;
		door = get_door(row + 1, col, cub3d);
	}
	door = get_door(row, col, cub3d);
	if (door != NULL)
		transition_door(door, DOOR_OPENING);
}

void	handle_collisions(t_cub3D *cub3d)
{
	t_player	*player;

	player = &cub3d->player;
	if (is_collision(player->x, player->prev_y, cub3d))
		handle_x_collision(player->x, player->prev_y, cub3d);
	if (is_collision(player->prev_x, player->y, cub3d))
		handle_y_collision(player->prev_x, player->y, cub3d);
	if (is_collision(player->x, player->y, cub3d))
	{
		handle_x_collision(player->x, player->y, cub3d);
		handle_y_collision(player->x, player->y, cub3d);
	}
}
