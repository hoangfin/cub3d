/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 12:44:59 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/19 14:27:11 by emansoor         ###   ########.fr       */
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
	render_image(img->ceiling, cub3d, 0, 0);
	render_image(img->floor, cub3d, 0, HEIGHT / 2);
	render_image(img->scene, cub3d, 0, 0);
	render_image(img->minimap_bg, cub3d, MINIMAP_X, MINIMAP_Y);
	render_image(img->minimap, cub3d, MINIMAP_X, MINIMAP_Y);
}
