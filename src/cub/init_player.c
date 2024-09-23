/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 10:18:50 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/22 23:32:41 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player_data(t_cub3D *cub3d, int32_t row, int32_t col)
{
	const char	direction = cub3d->map->grid[row][col];

	cub3d->player.prev_x = col * MAP_CELL_SIZE;
	cub3d->player.prev_y = row * MAP_CELL_SIZE;
	cub3d->player.x = cub3d->player.prev_x;
	cub3d->player.y = cub3d->player.prev_y;
	cub3d->player.speed = 62.5;
	cub3d->player.sprite = cub3d->asset.sprite_gun;
	cub3d->player.image = cub3d->player.sprite->frames[0][0];
	if (direction == 'N')
		cub3d->player.angle = M_PI / 2;
	if (direction == 'E')
		cub3d->player.angle = 0;
	if (direction == 'S')
		cub3d->player.angle = 3 * M_PI / 2;
	if (direction == 'W')
		cub3d->player.angle = M_PI;
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
