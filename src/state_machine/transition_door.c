/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_door.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:58:37 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 14:24:04 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"

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
