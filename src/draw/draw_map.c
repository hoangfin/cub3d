/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:16:53 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/27 15:57:36 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_doors(mlx_image_t *map, t_cub3D *cub3d)
{
	uint8_t *const	map_original = map->pixels;
	uint32_t		i;
	t_door			*door;

	i = 0;
	while (i < cub3d->map->door_count)
	{
		door = cub3d->doors + i;
		map->pixels = get_pixels(map, door->x, door->y);
		copy_pixels(map, cub3d->asset.door, MAP_CELL_SIZE, MAP_CELL_SIZE);
		map->pixels = map_original;
		i++;
	}
}

static void	fill_player(mlx_image_t *map, mlx_image_t *nav, t_cub3D *cub3d)
{
	uint8_t *const	map_original = map->pixels;
	uint8_t *const	nav_original = nav->pixels;

	map->pixels = get_pixels(map, cub3d->player.x, cub3d->player.y);
	nav->pixels = get_pixels(\
		nav, \
		((int32_t)(cub3d->player.angle * 36 / M_PI) % 9) * MAP_PLAYER_SIZE, \
		((int32_t)(cub3d->player.angle * 36 / M_PI) / 9) * MAP_PLAYER_SIZE \
	);
	copy_pixels(map, cub3d->asset.navigator, MAP_PLAYER_SIZE, MAP_PLAYER_SIZE);
	map->pixels = map_original;
	nav->pixels = nav_original;
}

void	draw_map(mlx_image_t *map, t_cub3D *cub3d)
{
	uint8_t	*player_pixels;

	player_pixels = get_pixels(\
		map, cub3d->player.prev_x, cub3d->player.prev_y \
	);
	clear_pixels(player_pixels, map->width, MAP_PLAYER_SIZE, MAP_PLAYER_SIZE);
	fill_doors(map, cub3d);
	fill_player(map, cub3d->asset.navigator, cub3d);
}
