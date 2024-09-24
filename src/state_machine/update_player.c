/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:10:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/24 19:07:34 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	handle_movement(t_player *player, double elapsed_time)
{
	const double	distance = player->speed * elapsed_time;
	double			move_angle;

	move_angle = player->angle;

	if (player->state & PLAYER_MOVING_BACKWARD)
		move_angle += M_PI;
	else if (player->state & PLAYER_MOVING_LEFT)
		move_angle += M_PI / 2;
	else if (player->state & PLAYER_MOVING_RIGHT)
		move_angle += 3 * M_PI / 2;
	player->prev_x = player->x;
	player->prev_y = player->y;
	player->x += distance * cos(move_angle);
	player->y -= distance * sin(move_angle);
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
