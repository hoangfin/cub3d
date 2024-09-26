/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_hit_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:15:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 19:43:48 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

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

void	find_hit_point(
			t_ray *ray,
			t_cub3D *cub3d,
			bool (*is_hit)(int32_t , int32_t , void *)
)
{
	double	distance_by_dx;
	double	distance_by_dy;
	int32_t	row_step;
	int32_t	col_step;

	ray->hit_row = ray->y_start / MAP_CELL_SIZE;
	ray->hit_col = ray->x_start / MAP_CELL_SIZE;
	init_dist_and_step_x(&distance_by_dx, &col_step, ray);
	init_dist_and_step_y(&distance_by_dy, &row_step, ray);
	while (!is_hit(ray->hit_row, ray->hit_col, cub3d))
	{
		if (distance_by_dx < distance_by_dy)
		{
			distance_by_dx += fabs(MAP_CELL_SIZE / ray->dir_x);
			ray->hit_col += col_step;
			ray->hit_side = 0;
		}
		else
		{
			distance_by_dy += fabs(MAP_CELL_SIZE / ray->dir_y);
			ray->hit_row += row_step;
			ray->hit_side = 1;
		}
	}
}
