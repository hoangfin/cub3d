/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 22:51:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 23:48:47 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_cub3D *cub3d)
{
	t_player *const	player = &cub3d->player;
	t_sprite *const	sprite = cub3d->player.sprite;
	int32_t			row;
	int32_t			col;

	row = player->frame_index / sprite->col_count;
	col = player->frame_index % sprite->col_count;
	copy_pixels(
		player->image,
		sprite->frames[row][col],
		player->image->width,
		player->image->height
	);
}