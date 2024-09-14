/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:57:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/15 01:27:30 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

static double	calc_perp_distance(double distance, double angle_diff)
{
	double	cos_value;

	if (angle_diff < 0)
		angle_diff += 2 * M_PI;
	if (angle_diff >= 2 * M_PI)
		angle_diff -= 2 * M_PI;
	cos_value = cos(angle_diff);
	return (distance * fabs(cos_value));
}

void	dda(t_ray *ray, t_cub3D *cub3d)
{
	// double	distance_x;
	// double	distance_y;
	// double	dx;
	// double	dy;
	// int32_t	map_x;
	// int32_t	map_y;
	// int32_t	step_x;
	// int32_t	step_y;
	// int32_t	side;

	// dx = fabs(MAP_CELL_SIZE / ray->dir_x);
	// dy = fabs(MAP_CELL_SIZE / ray->dir_y);
	// map_x = ray->x_start / MAP_CELL_SIZE;
	// map_y = ray->y_start / MAP_CELL_SIZE;

	// step_x = 1;
	// step_y = 1;
	// if (ray->dir_x < 0)
	// 	step_x = -1;
	// if (ray->dir_y > 0)
	// 	step_y = -1;

	// // printf("step_x=%d, step_y=%d\n", step_x, step_y);
	// side = 0;

	// if (is_equal(ray->dir_x, 0.0))
	// 	distance_x = DBL_MAX;
	// else if (ray->dir_x > 0)
	// 	distance_x = fabs((MAP_CELL_SIZE - fmod(ray->x_start, MAP_CELL_SIZE)) / ray->dir_x);
	// else
	// 	distance_x = fabs(fmod(ray->x_start, MAP_CELL_SIZE) / ray->dir_x) ;

	// if (is_equal(ray->dir_y, 0.0))
	// 	distance_y = DBL_MAX;
	// else if (ray->dir_y > 0)
	// 	distance_y = fabs(fmod(ray->y_start, MAP_CELL_SIZE) / ray->dir_y);
	// else
	// 	distance_y = fabs((MAP_CELL_SIZE - fmod(ray->y_start, MAP_CELL_SIZE)) / ray->dir_y);

	// // printf("dda::LOOP START\n");
	// while (
	// 	map_x >= 0 && (uint32_t)map_x < cub3d->map->col_count
	// 	&& map_y >= 0 && (uint32_t)map_y < cub3d->map->row_count
	// 	&& cub3d->map->grid[map_y][map_x] != MAP_WALL
	// )
	// {
	// 	// printf("Checking row=%d, col=%d, distance_x=%f, distance_y=%f\n", map_y, map_x, distance_x, distance_y);
	// 	if (distance_x < distance_y)
	// 	{
	// 		distance_x += dx;
	// 		map_x += step_x;
	// 		side = 0;
	// 	}
	// 	else
	// 	{
	// 		distance_y += dy;
	// 		map_y += step_y;
	// 		side = 1;
	// 	}
	// }
	// // printf("dda::LOOP END at row=%d, col=%d, side=%d, ray->dir_x=%f, ray->dir_y=%f, angle=%f\n", map_y, map_x, side, ray->dir_x, ray->dir_y, ray->angle * 180 / M_PI);
	// if (side == 0)
	// {
	// 	ray->x_end = map_x * MAP_CELL_SIZE;
	// 	if (ray->x_end < ray->x_start)
	// 		ray->x_end += MAP_CELL_SIZE;
	// 	ray->distance = fabs((ray->x_end - ray->x_start) / ray->dir_x);
	// 	ray->y_end = ray->y_start + step_y * fabs((ray->x_end - ray->x_start) * tan(ray->angle));
	// }
	// else
	// {
	// 	ray->y_end = map_y * MAP_CELL_SIZE;
	// 	if (ray->y_end < ray->y_start)
	// 		ray->y_end += MAP_CELL_SIZE;
	// 	ray->distance = fabs((ray->y_end - ray->y_start) / ray->dir_y);
	// 	ray->x_end = ray->x_start + step_x * fabs((ray->y_end - ray->y_start) / tan(ray->angle));

	// 	// printf("dda::END x_start=%f, x_end=%f, y_start=%f, y_end=%f\n", ray->x_start, ray->x_end, ray->y_start, ray->y_end);
	// }
	dda_set_end_point(ray, cub3d);
	ray->distance = fabs((ray->y_end - ray->y_start) / ray->dir_y);
	ray->distance = calc_perp_distance(\
		ray->distance, cub3d->player.angle - ray->angle \
	);
}
