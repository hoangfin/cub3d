/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:44:59 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/27 14:07:45 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	new_image(mlx_image_t **img, t_cub3D *cub, uint32_t w, uint32_t h)
{
	*img = mlx_new_image(cub->mlx, w, h);
	if (*img == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub);
		exit(EXIT_FAILURE);
	}
}

static void	fill_map_elements(mlx_image_t *map, char element, t_cub3D *cub3d)
{
	t_asset	*asset;

	asset = &cub3d->asset;
	if (element == MAP_WALL)
		copy_pixels(map, asset->obstacle, MAP_CELL_SIZE, MAP_CELL_SIZE);
	if (element == MAP_DOOR)
		copy_pixels(map, asset->door, MAP_CELL_SIZE, MAP_CELL_SIZE);
}

static void	fill_map(mlx_image_t *map, char **grid, t_cub3D *cub3d)
{
	uint8_t *const	original = map->pixels;
	uint32_t		row;
	uint32_t		col;

	row = 0;
	while (row < cub3d->map->row_count)
	{
		col = 0;
		while (col < cub3d->map->col_count)
		{
			map->pixels = get_pixels(\
				map, col * MAP_CELL_SIZE, row * MAP_CELL_SIZE \
			);
			fill_map_elements(map, grid[row][col], cub3d);
			map->pixels = original;
			col++;
		}
		row++;
	}
}

void	init_images(t_cub3D *cub3d)
{
	t_image	*image;

	image = &cub3d->image;
	new_image(&image->ceiling, cub3d, WIDTH, HEIGHT / 2);
	new_image(&image->floor, cub3d, WIDTH, HEIGHT / 2);
	new_image(&image->scene, cub3d, WIDTH, HEIGHT);
	new_image(&image->map, cub3d, cub3d->map->width, cub3d->map->height);
	new_image(&image->minimap_bg, cub3d, MINIMAP_SIZE, MINIMAP_SIZE);
	new_image(&image->minimap, cub3d, MINIMAP_SIZE, MINIMAP_SIZE);
	new_image(\
		&image->player, \
		cub3d, \
		cub3d->player.sprite->frame_w, \
		cub3d->player.sprite->frame_h \
	);
	fill(image->ceiling, cub3d->map->color_ceiling);
	fill(image->floor, cub3d->map->color_floor);
	fill(image->minimap_bg, color(36, 37, 39, 255));
	fill_map(image->map, cub3d->map->grid, cub3d);
}
