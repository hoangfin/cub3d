/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:18:50 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 21:37:45 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player_angle(t_player *player, const char direction)
{
	if (direction == 'N')
		player->angle = M_PI / 2;
	if (direction == 'E')
		player->angle = 0;
	if (direction == 'S')
		player->angle = 3 * M_PI / 2;
	if (direction == 'W')
		player->angle = M_PI;
}

static void	init_player_data(t_cub3D *cub3d, int32_t row, int32_t col)
{
	t_player	*player;

	player = &cub3d->player;
	init_player_angle(player, cub3d->map->grid[row][col]);
	player->prev_x = col * MAP_CELL_SIZE;
	player->prev_y = row * MAP_CELL_SIZE;
	player->x = player->prev_x;
	player->y = player->prev_y;
	player->speed = 62.5;
	player->state = PLAYER_IDLE;
	player->elapsed_time = 0.0;
	player->sprite = cub3d->asset.sprite_wand;
	player->frame_index = 0;
}

void	init_player(t_cub3D *cub3d)
{
	uint32_t	row;
	uint32_t	col;

	row = 0;
	while (row < cub3d->map->row_count)
	{
		col = 0;
		while (col < cub3d->map->col_count)
		{
			if (ft_strchr(MAP_PLAYER, cub3d->map->grid[row][col]) != NULL)
			{
				init_player_data(cub3d, row, col);
				return ;
			}
			col++;
		}
		row++;
	}
}
