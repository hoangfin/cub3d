/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:13:12 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 08:17:43 by hoatran          ###   ########.fr       */
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
	door->elapsed_time += elapsed_time;
	if (door->elapsed_time >= 0.3)
	{
		door->frame_index--;
		door->elapsed_time -= 0.3;
	}
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
