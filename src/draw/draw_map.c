/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 21:16:53 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/15 01:17:33 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void draw_line(mlx_image_t* img, int x0, int y0, int x1, int y1, uint32_t color)
{
    // Bresenham's line algorithm
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        // Set pixel at (x0, y0)
        mlx_put_pixel(img, x0, y0, color);

        // Break if the end point is reached
        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;

        // Adjust error and coordinates accordingly
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// static void	fill_rays(t_cub3D *cub3d)
// {
// 	int32_t	i;
// 	t_ray	ray;

// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		ray = cub3d->rays[i];
// 		draw_line(
// 			cub3d->image.map,
// 			ray.x_start,
// 			ray.y_start,
// 			ray.x_end,
// 			ray.y_end,
// 			color(78, 24, 155, 255)
// 		);
// 		i++;
// 	}
// }

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
	clear_image(cub3d->image.map);
	fill_obstacles(map, cub3d->map->grid, cub3d);
	fill_player(map, cub3d->asset.navigator, cub3d);
	// fill_rays(cub3d);
}
