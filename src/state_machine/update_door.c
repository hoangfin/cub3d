/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:13:12 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 15:05:12 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"

static void	handle_door_opening(t_door *door, double elapsed_time)
{
	int32_t	frame_index;

	door->elapsed_time += elapsed_time;
	frame_index = (uint32_t)door->elapsed_time % 9;
	
}

void	update_door(t_door *door, double elapsed_time)
{
	if (door->state == DOOR_OPENING)
		return (handle_door_opening(door, elapsed_time));
}
