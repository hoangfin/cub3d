/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:10:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/22 19:37:56 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}
