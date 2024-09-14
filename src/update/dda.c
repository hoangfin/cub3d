/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:57:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/14 19:07:18 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

// static bool	hit_diagonal_wall(t_ray start, t_ray end, t_cub3D *cub3d)
// {
// 	const int32_t	row = start.y_end / MAP_CELL_SIZE;
// 	const int32_t	col = start.x_end / MAP_CELL_SIZE;
// 	const int32_t	end_row = end.y_end / MAP_CELL_SIZE;
// 	const int32_t	end_col = end.x_end / MAP_CELL_SIZE;

// 	if (
// 		start.angle > M_PI / 2 && start.angle < M_PI
// 		&& row - 1 == end_row && col - 1 == end_col
// 		&& row - 1 >= 0 && col - 1 >= 0
// 		&& cub3d->map->grid[row - 1][col] == MAP_WALL
// 		&& cub3d->map->grid[row][col - 1] == MAP_WALL
// 	)
// 		return (true);
// 	if (
// 		start.angle > 0 && start.angle < M_PI / 2
// 		&& row - 1 == end_row && col + 1 == end_col
// 		&& row - 1 >= 0 && col + 1 < (int32_t)cub3d->map->col_count
// 		&& cub3d->map->grid[row - 1][col] == MAP_WALL
// 		&& cub3d->map->grid[row][col + 1] == MAP_WALL
// 	)
// 		return (true);
// 	if (
// 		start.angle > 3 * M_PI / 2 && start.angle < 2 * M_PI
// 		&& row + 1 == end_row && col + 1 == end_col
// 		&& row + 1 < (int32_t)cub3d->map->row_count && col + 1 < (int32_t)cub3d->map->col_count
// 		&& cub3d->map->grid[row + 1][col] == MAP_WALL
// 		&& cub3d->map->grid[row][col + 1] == MAP_WALL
// 	)
// 		return (true);
// 	if (
// 		start.angle > M_PI && start.angle < 3 * M_PI / 2
// 		&& row + 1 == end_row && col - 1 == end_col
// 		&& row + 1 < (int32_t)cub3d->map->row_count && col - 1 >= 0
// 		&& cub3d->map->grid[row + 1][col] == MAP_WALL
// 		&& cub3d->map->grid[row][col - 1] == MAP_WALL
// 	)
// 		return (true);
// 	return (false);
// }

// static void	step(t_ray *ray, double dx, double dy)
// {
// 	double	distance;

// 	if (ray->angle < M_PI / 2 || ray->angle > (3 * M_PI / 2))
// 		ray->x_end += dx;
// 	if (ray->angle > M_PI / 2 && ray->angle < (3 * M_PI / 2))
// 		ray->x_end -= dx;
// 	if (ray->angle > 0 && ray->angle < M_PI)
// 		ray->y_end -= dy;
// 	if (ray->angle > M_PI && ray->angle < 2 * M_PI)
// 		ray->y_end += dy;
// 	// distance = dx / cos(ray->angle);
// 	// ray->distance += fabs(distance);
// }

// static void	dda_x_axis(t_ray *ray, double dir_x, double dir_y, t_cub3D *cub3d)
// {
// 	double	dx;
// 	t_ray	temp;

// 	if (dir_x == 0)
// 	{
// 		ray->distance = DBL_MAX;
// 		return ;
// 	}
// 	if (dir_x > 0)
// 		dx = MAP_CELL_SIZE - fmod(ray->x_start, MAP_CELL_SIZE);
// 	if (dir_x < 0)
// 		dx = fmod(ray->x_start, MAP_CELL_SIZE) + 1;
// 	while (is_valid_position(ray->x_end, ray->y_end, cub3d))
// 	{
// 		temp = *ray;
// 		step(ray, dx, dx * fabs(tan(ray->angle)));
// 		if (hit_diagonal_wall(temp, *ray, cub3d))
// 			break ;
// 		dx = MAP_CELL_SIZE;
// 	}
// 	// ray->x_end = floor(ray->x_end);
// 	// ray->y_end = floor(ray->y_end);
// 	ray->distance = sqrt(
// 		(ray->x_end - ray->x_start) * (ray->x_end - ray->x_start)
// 		+ (ray->y_end - ray->y_start) * (ray->y_end - ray->y_start)
// 	);
// }

// static void	dda_y_axis(t_ray *ray, double dir_x, double dir_y, t_cub3D *cub3d)
// {
// 	double	dy;
// 	t_ray	temp;

// 	dir_y = sin(ray->angle);
// 	if (dir_y == 0)
// 	{
// 		ray->distance = DBL_MAX;
// 		return ;
// 	}
// 	if (dir_y > 0)
// 		dy = fmod(ray->y_start, MAP_CELL_SIZE) + 1;
// 	if (dir_y < 0)
// 		dy = MAP_CELL_SIZE - fmod(ray->y_start, MAP_CELL_SIZE);
// 	while (is_valid_position(ray->x_end, ray->y_end, cub3d))
// 	{
// 		temp = *ray;
// 		step(ray, dy / fabs(tan(ray->angle)), dy);
// 		if (hit_diagonal_wall(temp, *ray, cub3d))
// 			break ;
// 		dy = MAP_CELL_SIZE;
// 	}
// 	// ray->x_end = floor(ray->x_end);
// 	// ray->y_end = floor(ray->y_end);
// 	ray->distance = sqrt(
// 		(ray->x_end - ray->x_start) * (ray->x_end - ray->x_start)
// 		+ (ray->y_end - ray->y_start) * (ray->y_end - ray->y_start)
// 	);
// }

static bool	is_equal(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

void	dda(t_ray *ray, t_cub3D *cub3d)
{
	double	hit_angle;
	double	dir_x;
	double	dir_y;
	double	distance_x;
	double	distance_y;
	double	dx;
	double	dy;
	int32_t	map_x;
	int32_t	map_y;
	int32_t	step_x;
	int32_t	step_y;
	int32_t	side;

	dir_x = cos(ray->angle);
	dir_y = sin(ray->angle);
	dx = fabs(MAP_CELL_SIZE / dir_x);
	dy = fabs(MAP_CELL_SIZE / dir_y);
	map_x = ray->x_start / MAP_CELL_SIZE;
	map_y = ray->y_start / MAP_CELL_SIZE;

	step_x = 1;
	step_y = 1;
	if (dir_x < 0)
		step_x = -1;
	if (dir_y > 0)
		step_y = -1;

	// printf("step_x=%d, step_y=%d\n", step_x, step_y);
	side = 0;

	if (is_equal(dir_x, 0.0))
		distance_x = DBL_MAX;
	else if (dir_x > 0)
		distance_x = fabs((MAP_CELL_SIZE - fmod(ray->x_start, MAP_CELL_SIZE)) / dir_x);
	else
		distance_x = fabs(fmod(ray->x_start, MAP_CELL_SIZE) / dir_x) ;

	if (is_equal(dir_y, 0.0))
		distance_y = DBL_MAX;
	else if (dir_y > 0)
		distance_y = fabs(fmod(ray->y_start, MAP_CELL_SIZE) / dir_y);
	else
		distance_y = fabs((MAP_CELL_SIZE - fmod(ray->y_start, MAP_CELL_SIZE)) / dir_y);

	// printf("dda::LOOP START\n");
	while (
		map_x >= 0 && (uint32_t)map_x < cub3d->map->col_count
		&& map_y >= 0 && (uint32_t)map_y < cub3d->map->row_count
		&& cub3d->map->grid[map_y][map_x] != MAP_WALL
	)
	{
		// printf("Checking row=%d, col=%d, distance_x=%f, distance_y=%f\n", map_y, map_x, distance_x, distance_y);
		if (distance_x < distance_y)
		{
			distance_x += dx;
			map_x += step_x;
			side = 0;
		}
		else
		{
			distance_y += dy;
			map_y += step_y;
			side = 1;
		}
	}
	// printf("dda::LOOP END at row=%d, col=%d, side=%d, dir_x=%f, dir_y=%f, angle=%f\n", map_y, map_x, side, dir_x, dir_y, ray->angle * 180 / M_PI);
	if (side == 0)
	{
		ray->x_end = map_x * MAP_CELL_SIZE;
		if (ray->x_end < ray->x_start)
			ray->x_end += MAP_CELL_SIZE;
		ray->distance = fabs((ray->x_end - ray->x_start) / dir_x);
		ray->y_end = ray->y_start + step_y * fabs((ray->x_end - ray->x_start) * tan(ray->angle));
		printf("distance_x=%f, calc_distance_x=%f\n", distance_x, ray->distance);
	}
	else
	{
		ray->y_end = map_y * MAP_CELL_SIZE;
		if (ray->y_end < ray->y_start)
			ray->y_end += MAP_CELL_SIZE;
		ray->distance = fabs((ray->y_end - ray->y_start) / dir_y);
		ray->x_end = ray->x_start + step_x * fabs((ray->y_end - ray->y_start) / tan(ray->angle));
		printf("distance_y=%f, calc_distance_y=%f\n", distance_y, ray->distance);

		// printf("dda::END x_start=%f, x_end=%f, y_start=%f, y_end=%f\n", ray->x_start, ray->x_end, ray->y_start, ray->y_end);
	}
	// hit_angle = ray->angle - cub3d->player.angle;
	// if (hit_angle < 0)
	// 	hit_angle += 2 * M_PI;
	// if (hit_angle > 2 * M_PI)
	// 	hit_angle -= 2 * M_PI;
	// ray->distance = ray->distance / fabs(cos(hit_angle));
}
