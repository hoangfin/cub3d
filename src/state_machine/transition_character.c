/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transition_character.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 21:51:00 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/22 00:14:53 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "character.h"

void	transition_character(t_character *character, t_character_state state)
{
	if (character->state == CHAR_ATTACKING)
		return ;
	character->state = state;
}
