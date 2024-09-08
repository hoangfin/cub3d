/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:57:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/09 01:47:37 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

static bool	hit_diagonal_wall(t_ray *ray, double dx, double dy, t_cub3D *cub3d)
{
	const int32_t	row = ray->y_end / MAP_CELL_SIZE;
	const int32_t	col = ray->x_end / MAP_CELL_SIZE;
	int32_t			dest_row;
	int32_t			dest_col;
	t_ray			dest_ray;

	dest_ray = *ray;
	step(&dest_ray, dx, dy);
	dest_row = dest_ray.y_end / MAP_CELL_SIZE;
	dest_col = dest_ray.x_end / MAP_CELL_SIZE;
	if ()
}

static void	step(t_ray *ray, double dx, double dy)
{
	if (ray->angle < M_PI / 2 || ray->angle > (3 * M_PI / 2))
		ray->x_end += dx;
	if (ray->angle > M_PI / 2 && ray->angle < (3 * M_PI / 2))
		ray->x_end -= dx;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->y_end -= dy;
	if (ray->angle > M_PI && ray->angle < 2 * M_PI)
		ray->y_end += dy;
}

static void	dda_x_axis(t_ray *ray, t_cub3D *cub3d)
{
	double	dx;
	double	direction;

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
		step(ray, dx, dx * fabs(tan(ray->angle)));
		ray->distance += fabs(dx / direction);
		dx = MAP_CELL_SIZE;
	}
}

static void	dda_y_axis(t_ray *ray, t_cub3D *cub3d)
{
	double	dy;
	double	direction;

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
		step(ray, dy / fabs(tan(ray->angle)), dy);
		ray->distance += fabs(dy / direction);
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
