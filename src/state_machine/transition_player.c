/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 21:51:00 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 21:44:29 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	transition_player(t_player *player, t_player_state state)
{
	if (player->state == PLAYER_ATTACKING)
		return ;
	player->state = state;
}
