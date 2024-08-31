/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:18:50 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/31 10:53:22 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player_angle(t_character *player, const char direction)
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
				cub3d->player.x = col * MAP_CELL_SIZE;
				cub3d->player.y = row * MAP_CELL_SIZE;
				cub3d->player.speed = 62.5;
				init_player_angle(&cub3d->player, cub3d->map->grid[row][col]);
				return ;
			}
			col++;
		}
		row++;
	}
}
