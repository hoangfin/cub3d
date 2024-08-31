/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:16:53 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/29 23:20:31 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_obstacles(mlx_image_t *map, char **grid, t_cub3D *cub3d)
{
	uint8_t		*original;
	uint32_t	row;
	uint32_t	col;

	grid = cub3d->map->grid;
	original = map->pixels;
	row = 0;
	while (row < cub3d->map->row_count)
	{
		col = 0;
		while (col < cub3d->map->col_count)
		{
			map->pixels = get_pixels(
				map, col * MAP_CELL_SIZE, row * MAP_CELL_SIZE
			);
			if (grid[row][col] == MAP_WALL)
				copy_pixels(map, cub3d->asset.obstacle, MAP_CELL_SIZE, MAP_CELL_SIZE);
			map->pixels = original;
			col++;
		}
		row++;
	}
}

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
	fill(cub3d->image.map, color(36, 37, 39, 255));
	fill_obstacles(map, cub3d->map->grid, cub3d);
	fill_player(map, cub3d->asset.navigator, cub3d);
}
