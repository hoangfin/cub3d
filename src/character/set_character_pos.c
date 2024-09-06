/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_character_pos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:32:20 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/04 13:41:50 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_character_pos(double x, double y, t_cub3D *cub3D)
{
	if (
		!is_valid_position(x, y, cub3D)
		|| !is_valid_position(x + MAP_PLAYER_SIZE, y, cub3D)
		|| !is_valid_position(x, y + MAP_PLAYER_SIZE, cub3D)
		|| !is_valid_position(x + MAP_PLAYER_SIZE, y + MAP_PLAYER_SIZE, cub3D)
	)
		return ;
	cub3D->player.x = x;
	cub3D->player.y = y;
}
