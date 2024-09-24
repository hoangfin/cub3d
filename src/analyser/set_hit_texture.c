/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hit_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:42:17 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/24 12:25:23 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_wall_texture(t_ray *ray, mlx_image_t *walls[])
{
	int32_t	pos_index;

	if (ray->hit_side == 0)
	{
		ray->hit_texture = walls[3];
		if (ray->x_end < ray->x_start)
			ray->hit_texture = walls[1];
		pos_index = (int32_t)ray->y_end % MAP_CELL_SIZE;
		ray->hit_texture_pos_x = pos_index * ray->hit_texture->width / MAP_CELL_SIZE;
	}
	else
	{
		ray->hit_texture = walls[0];
		if (ray->y_end < ray->y_start)
			ray->hit_texture = walls[2];
		pos_index = (int32_t)ray->x_end % MAP_CELL_SIZE;
		ray->hit_texture_pos_x = pos_index * ray->hit_texture->width / MAP_CELL_SIZE;
	}
}

static void	set_door_texture(t_ray *ray, mlx_image_t *door)
{
	int32_t	pos_index;

	// printf("door:width=%d, height=%d\n", door->width, door->height);
	ray->hit_texture = door;
	if (ray->hit_side == 0)
	{
		pos_index = (int32_t)ray->y_end % MAP_CELL_SIZE;
		ray->hit_texture_pos_x = pos_index * door->width / MAP_CELL_SIZE;
	}
	else
	{
		pos_index = (int32_t)ray->x_end % MAP_CELL_SIZE;
		ray->hit_texture_pos_x = pos_index * door->width / MAP_CELL_SIZE;
	}
}

void	set_hit_texture(int32_t row, int32_t col, t_ray *ray, t_cub3D *cub3d)
{
	t_door	*door;

	if (cub3d->map->grid[row][col] == MAP_DOOR)
	{
		door = get_door(row, col, cub3d);
		set_door_texture(ray, door->image);
	}
	else if (cub3d->map->grid[row][col] == MAP_WALL)
		set_wall_texture(ray, cub3d->asset.walls);
}
