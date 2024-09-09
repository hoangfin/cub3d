/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:57:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/09 15:26:41 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

static bool	hit_diagonal_wall(t_ray start, t_ray end, t_cub3D *cub3d)
{
	const int32_t	row = start.y_end / MAP_CELL_SIZE;
	const int32_t	col = start.x_end / MAP_CELL_SIZE;
	const int32_t	end_row = end.y_end / MAP_CELL_SIZE;
	const int32_t	end_col = end.x_end / MAP_CELL_SIZE;

	if (
		end.x_end < 0 || end.x_end >= cub3d->map->width
		|| end.y_end < 0 || end.y_end >= cub3d->map->height)
		return (false);

	if (start.angle > M_PI / 2 && start.angle < M_PI && row - 1 == end_row && col - 1 == end_col
		&& row - 1 >= 0 && cub3d->map->grid[row - 1][col] == MAP_WALL
		&& col - 1 >= 0 && cub3d->map->grid[row][col - 1] == MAP_WALL
	)
		return (true);
	if (
		start.angle > 0 && start.angle < M_PI / 2
		&& row - 1 == end_row && col + 1 == end_col
		&& row - 1 >= 0 && cub3d->map->grid[row - 1][col] == MAP_WALL
		&& col + 1 < (int32_t)cub3d->map->col_count && cub3d->map->grid[row][col + 1] == MAP_WALL
	)
		return (true);
	if (
		start.angle > 3 * M_PI / 2 && start.angle < 2 * M_PI
		&& row + 1 == end_row && col + 1 == end_col
		&& row + 1 < (int32_t)cub3d->map->row_count && cub3d->map->grid[row + 1][col] == MAP_WALL
		&& col + 1 < (int32_t)cub3d->map->col_count && cub3d->map->grid[row][col + 1] == MAP_WALL
	)
		return (true);
	if (
		start.angle > M_PI && start.angle < 3 * M_PI / 2
		&& row + 1 == end_row && col - 1 == end_col
		&& row + 1 < (int32_t)cub3d->map->row_count && cub3d->map->grid[row + 1][col] == MAP_WALL
		&& col - 1 >= 0 && cub3d->map->grid[row][col - 1] == MAP_WALL
	)
		return (true);
	return (false);
}

static void	step(t_ray *ray, double dx, double dy)
{
	double	distance;

	if (ray->angle < M_PI / 2 || ray->angle > (3 * M_PI / 2))
		ray->x_end += dx;
	if (ray->angle > M_PI / 2 && ray->angle < (3 * M_PI / 2))
		ray->x_end -= dx;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->y_end -= dy;
	if (ray->angle > M_PI && ray->angle < 2 * M_PI)
		ray->y_end += dy;
	distance = dx / cos(ray->angle);
	ray->distance += fabs(distance);
}

static void	dda_x_axis(t_ray *ray, t_cub3D *cub3d)
{
	double	dx;
	double	direction;
	t_ray	temp;

	direction = cos(ray->angle);
	if (direction == 0)
	{
		ray->distance = DBL_MAX;
		return ;
	}
	if (direction > 0)
		dx = MAP_CELL_SIZE - fmod(ray->x_start, MAP_CELL_SIZE);
	if (direction < 0)
		dx = fmod(ray->x_start, MAP_CELL_SIZE) + 1;
	while (is_valid_position(ray->x_end, ray->y_end, cub3d))
	{
		temp = *ray;
		step(ray, dx, dx * fabs(tan(ray->angle)));
		if (hit_diagonal_wall(temp, *ray, cub3d))
			break ;
		dx = MAP_CELL_SIZE;
	}
}

static void	dda_y_axis(t_ray *ray, t_cub3D *cub3d)
{
	double	dy;
	double	direction;
	t_ray	temp;

	direction = sin(ray->angle);
	if (direction == 0)
	{
		ray->distance = DBL_MAX;
		return ;
	}
	if (direction > 0)
		dy = fmod(ray->y_start, MAP_CELL_SIZE) + 1;
	if (direction < 0)
		dy = MAP_CELL_SIZE - fmod(ray->y_start, MAP_CELL_SIZE);
	while (is_valid_position(ray->x_end, ray->y_end, cub3d))
	{
		temp = *ray;
		step(ray, dy / fabs(tan(ray->angle)), dy);
		if (hit_diagonal_wall(temp, *ray, cub3d))
			break ;
		dy = MAP_CELL_SIZE;
	}
}

void	dda(t_ray *ray, t_cub3D *cub3d)
{
	t_ray	ray_a;
	t_ray	ray_b;

	ray_a = *ray;
	ray_b = *ray;
	dda_x_axis(&ray_a, cub3d);
	dda_y_axis(&ray_b, cub3d);
	if (ray_a.distance < ray_b.distance)
		*ray = ray_a;
	else
		*ray = ray_b;
}
