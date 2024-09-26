/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:16:53 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 15:17:33 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_player(mlx_image_t *map, mlx_image_t *nav, t_cub3D *cub3d)
{
	uint8_t *const	map_original = map->pixels;
	uint8_t *const	nav_original = nav->pixels;

	map->pixels = get_pixels(map, cub3d->player.x, cub3d->player.y);
	nav->pixels = get_pixels(
		nav,
		((int32_t)(cub3d->player.angle * 36 / M_PI) % 9) * 16,
		((int32_t)(cub3d->player.angle * 36 / M_PI) / 9) * 16
	);
	copy_pixels(map, cub3d->asset.navigator, 16, 16);
	map->pixels = map_original;
	nav->pixels = nav_original;
}

void	draw_map(mlx_image_t *map, t_cub3D *cub3d)
{
	uint8_t	*player_pixels;

	player_pixels = get_pixels(
		map, cub3d->player.prev_x, cub3d->player.prev_y
	);
	clear_pixels(player_pixels, map->width, 16, 16);
	fill_player(map, cub3d->asset.navigator, cub3d);
}
