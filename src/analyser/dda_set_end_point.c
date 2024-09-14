/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_set_end_point.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:55:20 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/15 01:07:39 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

static void	step(int32_t *row, int32_t *col, double dir_x, double dir_y)
{
	int32_t	row_step;
	int32_t	col_step;

	col_step = 1;
	row_step = 1;
	if (dir_x < 0)
		col_step = -1;
	if (dir_y > 0)
		row_step = -1;
	if (row != NULL)
		*row += row_step;
	if (col != NULL)
		*col += col_step;
}

static bool	is_hit(int32_t row, int32_t col, t_cub3D *cub3d)
{
	if (row < 0 || (uint32_t)row >= cub3d->map->row_count)
		return (false);
	if (col < 0 || (uint32_t)col >= cub3d->map->col_count)
		return (false);
	return (cub3d->map->grid[row][col] == MAP_WALL);
}

static void	init_distance(double *dist_by_dx, double *dist_by_dy, t_ray *ray)
{
	const double	cur_pos_x = fmod(ray->x_start, MAP_CELL_SIZE);
	const double	cur_pos_y = fmod(ray->y_start, MAP_CELL_SIZE);

	if (is_equal(ray->dir_x, 0.0))
		*dist_by_dx = DBL_MAX;
	else if (ray->dir_x > 0)
		*dist_by_dx = fabs((MAP_CELL_SIZE - cur_pos_x) / ray->dir_x);
	else
		*dist_by_dx = fabs(cur_pos_x / ray->dir_x) ;
	if (is_equal(ray->dir_y, 0.0))
		*dist_by_dy = DBL_MAX;
	else if (ray->dir_y > 0)
		*dist_by_dy = fabs(cur_pos_y / ray->dir_y);
	else
		*dist_by_dy = fabs((MAP_CELL_SIZE - cur_pos_y) / ray->dir_y);
}

static void	find_hit_point(int32_t *row, int32_t *col, t_ray *ray, t_cub3D *cub3d)
{
	double	distance_by_dx;
	double	distance_by_dy;

	*row = ray->y_start / MAP_CELL_SIZE;
	*col = ray->x_start / MAP_CELL_SIZE;
	init_distance(&distance_by_dx, &distance_by_dy, ray);
	while (!is_hit(*row, *col, cub3d))
	{
		if (distance_by_dx < distance_by_dy)
		{
			distance_by_dx += ray->dx;
			step(NULL, col, ray->dir_x, ray->dir_y);
			ray->hit_side = 0;
		}
		else
		{
			distance_by_dy += ray->dy;
			step(row, NULL, ray->dir_x, ray->dir_y);
			ray->hit_side = 1;
		}
	}
}

void	dda_set_end_point(t_ray *ray, t_cub3D *cub3d)
{
	int32_t	row;
	int32_t	col;
	double	displacement;

	find_hit_point(&row, &col, ray, cub3d);
	if (ray->hit_side == 0)
	{
		ray->x_end = col * MAP_CELL_SIZE;
		if (ray->x_end < ray->x_start)
			ray->x_end += MAP_CELL_SIZE;
		displacement = fabs((ray->x_end - ray->x_start) * tan(ray->angle));
		if (ray->dir_y > 0)
			ray->y_end = ray->y_start - displacement;
		else
			ray->y_end = ray->y_start + displacement;
	}
	else
	{
		ray->y_end = row * MAP_CELL_SIZE;
		if (ray->y_end < ray->y_start)
			ray->y_end += MAP_CELL_SIZE;
		displacement = fabs((ray->y_end - ray->y_start) / tan(ray->angle));
		if (ray->dir_x > 0)
			ray->x_end = ray->x_start + displacement;
		else
			ray->x_end = ray->x_start - displacement;
	}
}
