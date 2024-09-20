/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:32:19 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 15:45:18 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	transition_door(t_door *door, t_door_state state)
{
	if (door->state == DOOR_OPENING || door->state == DOOR_CLOSING)
		return ;
	if (door->state == DOOR_OPEN)
	{
		if (state == DOOR_OPENING || state == DOOR_CLOSED)
			return ;
	}
	if (door->state == DOOR_CLOSED)
	{
		if (state == DOOR_CLOSING || state == DOOR_OPEN)
		return ;
	}
	door->state = state;
}

static void	handle_door_opening(t_door *door, double elapsed_time)
{
	int32_t	frame_index;

	door->elapsed_time += elapsed_time;
	frame_index = (uint32_t)door->elapsed_time % 9;

}

static void	update_door(t_door *door, double elapsed_time)
{
	if (door->state == DOOR_OPENING)
		return (handle_door_opening(door, elapsed_time));
}

void	update_doors(t_cub3D *cub3d, double elapsed_time)
{
	int32_t	i;

	i = 0;
	while (i < cub3d->map->door_count)
	{

		i++;
	}
}
