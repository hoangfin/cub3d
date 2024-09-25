/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:44:59 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 15:08:53 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	create_image(
	mlx_image_t **image,
	t_cub3D *cub3d,
	uint32_t width,
	uint32_t height
)
{
	*image = mlx_new_image(cub3d->mlx, width, height);
	if (*image == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(EXIT_FAILURE);
	}
}

static void	render_image(
	mlx_image_t *image,
	t_cub3D *cub3d,
	int32_t x,
	int32_t y
)
{
	if (mlx_image_to_window(cub3d->mlx, image, x, y) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(EXIT_FAILURE);
	}
}

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

void	create_images(t_cub3D *cub3d)
{
	t_image	*img;

	img = &cub3d->image;
	create_image(&img->ceiling, cub3d, WIDTH, HEIGHT / 2);
	create_image(&img->floor, cub3d, WIDTH, HEIGHT / 2);
	create_image(&img->scene, cub3d, WIDTH, HEIGHT);
	create_image(&img->map, cub3d, cub3d->map->width, cub3d->map->height);
	create_image(&img->minimap_bg, cub3d, MINIMAP_SIZE, MINIMAP_SIZE);
	create_image(&img->minimap, cub3d, MINIMAP_SIZE, MINIMAP_SIZE);
	fill(img->ceiling, cub3d->map->color_ceiling);
	fill(img->floor, cub3d->map->color_floor);
	fill(img->minimap_bg, color(36, 37, 39, 255));
	fill_obstacles(img->map, cub3d->map->grid, cub3d);
	render_image(img->ceiling, cub3d, 0, 0);
	render_image(img->floor, cub3d, 0, HEIGHT / 2);
	render_image(img->scene, cub3d, 0, 0);
	render_image(img->minimap_bg, cub3d, MINIMAP_X, MINIMAP_Y);
	render_image(img->minimap, cub3d, MINIMAP_X, MINIMAP_Y);
	// render_image(img->scene, cub3d, 0, 0);
	render_image(cub3d->player.image, cub3d, WIDTH / 2, HEIGHT - cub3d->player.image->height);
	// render_image(cub3d->doors[0].image, cub3d, 0, 0);
}
