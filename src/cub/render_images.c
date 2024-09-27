/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:23:52 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 21:43:15 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw(mlx_image_t *image, t_cub3D *cub3d, int32_t x, int32_t y)
{
	if (mlx_image_to_window(cub3d->mlx, image, x, y) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(EXIT_FAILURE);
	}
}

void	render_images(t_cub3D *cub3d)
{
	t_image	*image;

	image = &cub3d->image;
	draw(image->ceiling, cub3d, 0, 0);
	draw(image->floor, cub3d, 0, HEIGHT / 2);
	draw(image->scene, cub3d, 0, 0);
	draw(image->minimap_bg, cub3d, MINIMAP_X, MINIMAP_Y);
	draw(image->minimap, cub3d, MINIMAP_X, MINIMAP_Y);
	draw(image->player, cub3d, WIDTH / 2, HEIGHT - image->player->height);
}
