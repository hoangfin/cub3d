/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_collisions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 10:37:07 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/27 14:13:50 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	door_contains(t_door *door, int32_t x, int32_t y)
{
	const int32_t	door_row = door->y / MAP_CELL_SIZE;
	const int32_t	door_col = door->x / MAP_CELL_SIZE;
	int32_t			row;
	int32_t			col;

	if (x < 0 || y < 0)
		return (false);
	row = y / MAP_CELL_SIZE;
	col = x / MAP_CELL_SIZE;
	if (door_row == row && door_col == col)
		return (true);
	return (false);
}

static void	handle_door_collision(t_cub3D *cub3d)
{
	uint32_t	i;
	t_player	player;
	t_door		*door;
	bool		hit;

	i = 0;
	player = cub3d->player;
	while (i < cub3d->map->door_count)
	{
		door = cub3d->doors + i;
		hit = door_contains(door, player.x, player.y)
			|| door_contains(door, player.x + MAP_PLAYER_SIZE, player.y)
			|| door_contains(door, player.x, player.y + MAP_PLAYER_SIZE)
			|| door_contains(\
				door, player.x + MAP_PLAYER_SIZE, player.y + MAP_PLAYER_SIZE \
			);
		if (door->state != DOOR_OPEN && hit)
			transition_door(door, DOOR_OPENING);
		i++;
	}
}

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
	t_player *const	player = &cub3d->player;
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
	handle_door_collision(cub3d);
	handle_wall_collision(cub3d);
}
