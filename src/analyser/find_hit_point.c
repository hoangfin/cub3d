/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ray_hit_point.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:15:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/19 21:02:30 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

static bool	is_hit(int32_t row, int32_t col, t_cub3D *cub3d)
{
	if (row < 0 || (uint32_t)row >= cub3d->map->row_count)
		return (false);
	if (col < 0 || (uint32_t)col >= cub3d->map->col_count)
		return (false);
	if (cub3d->map->grid[row][col] == MAP_DOOR)
		return (true);
	return (cub3d->map->grid[row][col] == MAP_WALL);
}

static void	init_dist_and_step_x(
	double *dist_by_dx,
	int32_t *col_step,
	t_ray *ray
)
{
	const double	cur_pos_x = fmod(ray->x_start, MAP_CELL_SIZE);

	*dist_by_dx = DBL_MAX;
	*col_step = 1;
	if (ray->dir_x > 0)
		*dist_by_dx = fabs((MAP_CELL_SIZE - cur_pos_x) / ray->dir_x);
	if (ray->dir_x < 0)
	{
		*dist_by_dx = fabs(cur_pos_x / ray->dir_x);
		*col_step = -1;
	}
}

static void	init_dist_and_step_y(
	double *dist_by_dy,
	int32_t *row_step,
	t_ray *ray
)
{
	const double	cur_pos_y = fmod(ray->y_start, MAP_CELL_SIZE);

	*dist_by_dy = DBL_MAX;
	*row_step = 1;
	if (ray->dir_y > 0)
	{
		*dist_by_dy = fabs(cur_pos_y / ray->dir_y);
		*row_step = -1;
	}
	else
		*dist_by_dy = fabs((MAP_CELL_SIZE - cur_pos_y) / ray->dir_y);
}

void	find_hit_point(int32_t *row, int32_t *col, t_ray *ray, t_cub3D *cub3d)
{
	double	distance_by_dx;
	double	distance_by_dy;
	int32_t	row_step;
	int32_t	col_step;

	init_dist_and_step_x(&distance_by_dx, &col_step, ray);
	init_dist_and_step_y(&distance_by_dy, &row_step, ray);
	while (!is_hit(*row, *col, cub3d))
	{
		if (distance_by_dx < distance_by_dy)
		{
			distance_by_dx += fabs(MAP_CELL_SIZE / ray->dir_x);
			*col += col_step;
			ray->hit_side = 0;
		}
		else
		{
			distance_by_dy += fabs(MAP_CELL_SIZE / ray->dir_y);
			*row += row_step;
			ray->hit_side = 1;
		}
	}
}
