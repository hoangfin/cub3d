/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:13:12 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 23:35:17 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"

static void	handle_door_opening(t_door *door, double elapsed_time)
{
	door->elapsed_time += elapsed_time;
	door->frame_index = door->elapsed_time / 0.3;
	if (door->frame_index == (int32_t)door->sprite->col_count - 1)
	{
		door->state = DOOR_OPEN;
		door->elapsed_time = 0.0;
	}
}

static void	handle_door_closing(t_door *door, double elapsed_time)
{
	int32_t	frame_passed;

	frame_passed = 0;
	door->elapsed_time += elapsed_time;
	frame_count = door->elapsed_time / 0.3;
	door->frame_index =
	if (door->frame_index == 0)
	{
		door->state = DOOR_CLOSED;
		door->elapsed_time = 0.0;
	}
}

void	update_door(t_door *door, double elapsed_time)
{
	if (door->state == DOOR_CLOSED)
		door->frame_index = 0;
	else if (door->state == DOOR_OPEN)
		door->frame_index = (int32_t)door->sprite->col_count - 1;
	else if (door->state == DOOR_OPENING)
		handle_door_opening(door, elapsed_time);
	else if (door->state == DOOR_CLOSING)
		handle_door_closing(door, elapsed_time);
}
