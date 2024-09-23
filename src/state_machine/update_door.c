/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:13:12 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 14:24:47 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"

static void	handle_door_opening(t_door *door, double elapsed_time)
{
	const uint32_t	row = 0;
	uint32_t		col;

	door->elapsed_time += elapsed_time;
	col = (uint32_t)(door->elapsed_time / 0.099) % door->sprite->col_count;
	door->image = door->sprite->frames[row][col];
	if (col == door->sprite->col_count - 1)
	{
		door->state = DOOR_OPEN;
		door->elapsed_time = 0.0;
	}
}

void	update_door(t_door *door, double elapsed_time)
{
	if (door->state == DOOR_CLOSED)
		door->image = door->sprite->frames[0][0];
	else if (door->state == DOOR_OPEN)
		door->image = door->sprite->frames[0][door->sprite->col_count - 1];
	else if (door->state == DOOR_OPENING)
		handle_door_opening(door, elapsed_time);
}
