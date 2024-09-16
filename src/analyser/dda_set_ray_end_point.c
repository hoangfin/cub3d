/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_set_ray_end_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:55:20 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/17 00:36:56 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	handle_horizontal_hit(int32_t col_hit, t_ray *ray,t_cub3D *cub3d)
{
	double	dy;

	ray->x_end = col_hit * MAP_CELL_SIZE;
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
	ray->hit_texture_pos_x = ((int32_t)ray->y_end % MAP_CELL_SIZE) * 128 / MAP_CELL_SIZE;
}

static void	handle_vertical_hit(int32_t row_hit, t_ray *ray,t_cub3D *cub3d)
{
	double	dx;

	ray->y_end = row_hit * MAP_CELL_SIZE;
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
	ray->hit_texture_pos_x = ((int32_t)ray->x_end % MAP_CELL_SIZE) * 128 / MAP_CELL_SIZE;
}

void	dda_set_ray_end_point(
	int32_t row_hit,
	int32_t col_hit,
	t_ray *ray,
	t_cub3D *cub3d
)
{
	if (ray->hit_side == 0)
		handle_horizontal_hit(col_hit, ray, cub3d);
	else
		handle_vertical_hit(row_hit, ray, cub3d);
}
