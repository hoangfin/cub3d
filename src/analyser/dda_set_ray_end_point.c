/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_set_ray_end_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:55:20 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 13:43:24 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	handle_horizontal_hit(int32_t col, t_ray *ray, t_cub3D *cub3d)
{
	double	dy;
	double	factor;
	//int32_t	pos_index;

	ray->x_end = col * MAP_CELL_SIZE;
	ray->hit_texture = cub3d->asset.walls[3];
	if (ray->x_end < ray->x_start)
	{
		ray->x_end += MAP_CELL_SIZE;
		ray->hit_texture = cub3d->asset.walls[1];
	}
	dy = fabs((ray->x_end - ray->x_start) * ray->dir_y / ray->dir_x);
	if (ray->dir_y > 0)
		ray->y_end = ray->y_start - dy;
	else
		ray->y_end = ray->y_start + dy;
	factor = ray->x_end / WIDTH;
	ray->hit_texture_pos_x = (int32_t)(factor * ray->hit_texture->width);
	//pos_index = (int32_t)ray->y_end % MAP_CELL_SIZE;
	//ray->hit_texture_pos_x = pos_index * TEXTURE_SIZE / MAP_CELL_SIZE;
}

static void	handle_vertical_hit(int32_t row, t_ray *ray, t_cub3D *cub3d)
{
	double	dx;
	double	factor;
	//int32_t	pos_index;

	ray->y_end = row * MAP_CELL_SIZE;
	ray->hit_texture = cub3d->asset.walls[0];
	if (ray->y_end < ray->y_start)
	{
		ray->y_end += MAP_CELL_SIZE;
		ray->hit_texture = cub3d->asset.walls[2];
	}
	dx = fabs((ray->y_end - ray->y_start) * ray->dir_x / ray->dir_y);
	if (ray->dir_x > 0)
		ray->x_end = ray->x_start + dx;
	else
		ray->x_end = ray->x_start - dx;
	factor = ray->x_end / WIDTH;
	ray->hit_texture_pos_x = (int32_t)(factor * ray->hit_texture->width);
	//pos_index = (int32_t)ray->x_end % MAP_CELL_SIZE;
	//ray->hit_texture_pos_x = pos_index * TEXTURE_SIZE / MAP_CELL_SIZE;
}

void	dda_set_ray_end_point(
			int32_t row,
			int32_t col,
			t_ray *ray,
			t_cub3D *cub3d
)
{
	if (ray->hit_side == 0)
		handle_horizontal_hit(col, ray, cub3d);
	else
		handle_vertical_hit(row, ray, cub3d);
}
