/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:10:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 17:22:35 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "character.h"

static void	handle_turn(t_character *player)
{
	if (!(player->state & (CHAR_TURNING_LEFT | CHAR_TURNING_RIGHT)))
		return ;
	if (player->state & CHAR_TURNING_LEFT)
		player->angle -= M_PI / 36;
	if (player->state & CHAR_TURNING_RIGHT)
		player->angle += M_PI / 36;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	if (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;
}

static void	handle_movement(t_character *player, double elapsed_time)
{
	const double	distance = player->speed * elapsed_time;
	double			move_angle;

	move_angle = player->angle;
	if (player->state & CHAR_MOVING_BACKWARD)
		move_angle += M_PI;
	else if (player->state & CHAR_MOVING_LEFT)
		move_angle += M_PI / 2;
	else if (player->state & CHAR_MOVING_RIGHT)
		move_angle += 3 * M_PI / 2;
	player->prev_x = player->x;
	player->prev_y = player->y;
	player->x += distance * cos(move_angle);
	player->y -= distance * sin(move_angle);
}

static void	handle_attacking(t_character *player, double elapsed_time)
{
	const uint32_t	row = 0;
	uint32_t		col;

	player->elapsed_time += elapsed_time;
	col = (uint32_t)(player->elapsed_time / 0.099) % player->sprite->col_count;
	printf("handle_attacking::col=%d\n", col);
	player->image = player->sprite->frames[row][col];
	if (col == player->sprite->col_count - 1)
	{
		player->state = CHAR_IDLE;
		printf("player->state = CHAR_IDLE\n");
		player->elapsed_time = 0.0;
	}
}

void	update_character(t_character *character, double elapsed_time)
{
	t_character_state	move_mask;

	handle_turn(character);
	move_mask = (\
		CHAR_MOVING_FORWARD \
		| CHAR_MOVING_BACKWARD \
		| CHAR_MOVING_LEFT \
		| CHAR_MOVING_RIGHT \
	);
	if (character->state & move_mask)
		handle_movement(character, elapsed_time);
	else if (character->state == CHAR_ATTACKING)
		handle_attacking(character, elapsed_time);
}
