/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:28:51 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/29 23:25:29 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_x(int32_t *x, int32_t *offset_x, t_cub3D *cub3d)
{
	*offset_x = MINIMAP_SIZE;
	*x = max(cub3d->player.x - MINIMAP_SIZE / 2, 0);
	if (*((uint32_t *)x)+ MINIMAP_SIZE > cub3d->map->width)
	{
		*x = max(cub3d->map->width - MINIMAP_SIZE, 0);
		if (*x == 0)
			*offset_x = cub3d->map->width;
	}
}

static void	init_y(int32_t *y, int32_t *offset_y, t_cub3D *cub3d)
{
	*offset_y = MINIMAP_SIZE;
	*y = max(cub3d->player.y - MINIMAP_SIZE / 2, 0);
	if (*((uint32_t *)y) + MINIMAP_SIZE > cub3d->map->height)
	{
		*y = max(cub3d->map->height - MINIMAP_SIZE, 0);
		if (*y == 0)
			*offset_y = cub3d->map->height;
	}
}

void	draw_minimap(mlx_image_t *minimap, t_cub3D *cub3d)
{
	uint8_t	*original;
	int32_t	x;
	int32_t	y;
	int32_t	offset_x;
	int32_t	offset_y;

	original = cub3d->image.map->pixels;
	init_x(&x, &offset_x, cub3d);
	init_y(&y, &offset_y, cub3d);
	cub3d->image.map->pixels = get_pixels(cub3d->image.map, x, y);
	copy_pixels(minimap, cub3d->image.map, offset_x, offset_y);
	cub3d->image.map->pixels = original;
}
