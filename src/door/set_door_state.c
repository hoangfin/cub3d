/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_door_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 22:17:06 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/18 11:56:19 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door.h"

void	set_door_state(t_door_state *state, t_door_state new_state)
{
	if (*state == DOOR_OPENING || *state == DOOR_CLOSING)
		return ;
	*state = new_state;
}