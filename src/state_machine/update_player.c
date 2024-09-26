/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:10:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 16:51:01 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "player.h"

static void	handle_turn(t_player *player)
{
	if (!(player->state & (PLAYER_TURNING_LEFT | PLAYER_TURNING_RIGHT)))
		return ;
	if (player->state & PLAYER_TURNING_LEFT)
		player->angle -= M_PI / 36;
	if (player->state & PLAYER_TURNING_RIGHT)
		player->angle += M_PI / 36;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	if (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;
}

static void	set_direction(double *dir_x, double *dir_y, t_player *player)
{
	if (player->state & PLAYER_MOVING_FORWARD)
	{
		*dir_x += cos(player->angle);
		*dir_y -= sin(player->angle);
	}
	if (player->state & PLAYER_MOVING_BACKWARD)
	{
		*dir_x += cos(player->angle + M_PI);
		*dir_y -= sin(player->angle + M_PI);
	}
	if (player->state & PLAYER_MOVING_RIGHT)
	{
		*dir_x += cos(player->angle + 3 * M_PI / 2);
		*dir_y -= sin(player->angle + 3 * M_PI / 2);
	}
	if (player->state & PLAYER_MOVING_LEFT)
	{
		*dir_x += cos(player->angle + M_PI / 2);
		*dir_y -= sin(player->angle + M_PI / 2);
	}
}

static void	handle_movement(t_player *player, double elapsed_time)
{
	const double	distance = player->speed * elapsed_time;
	double			dir_x;
	double			dir_y;
	double			magnitude;

	dir_x = 0;
	dir_y = 0;
	set_direction(&dir_x, &dir_y, player);
	magnitude = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (magnitude - 0.0 > 1e-9)
	{
		dir_x /= magnitude;
		dir_y /= magnitude;
	}
	player->prev_x = player->x;
	player->prev_y = player->y;
	player->x += dir_x * distance;
	player->y += dir_y * distance;
}

static void	handle_attacking(t_player *player, double elapsed_time)
{
	player->elapsed_time += elapsed_time;
	player->frame_index = player->elapsed_time / 0.099;
	if (player->frame_index == (int32_t)player->sprite->col_count - 1)
	{
		player->state = PLAYER_IDLE;
		player->frame_index = 0;
		player->elapsed_time = 0.0;
	}
}

void	update_player(t_player *player, double elapsed_time)
{
	t_player_state	move_mask;

	handle_turn(player);
	move_mask = (\
		PLAYER_MOVING_FORWARD \
		| PLAYER_MOVING_BACKWARD \
		| PLAYER_MOVING_LEFT \
		| PLAYER_MOVING_RIGHT \
	);
	if (player->state & move_mask)
		handle_movement(player, elapsed_time);
	else if (player->state == PLAYER_ATTACKING)
		handle_attacking(player, elapsed_time);
}
