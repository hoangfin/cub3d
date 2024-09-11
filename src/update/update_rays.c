/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:47:12 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/11 14:51:25 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <float.h>
#include "cub3D.h"

static void	step_x_axis(double *x, double dx, double angle)
{
	if (angle < M_PI / 2 || angle > (3 * M_PI / 2))
		*x += dx;
	else if (angle > M_PI / 2 && angle < (3 * M_PI / 2))
		*x -= dx;
}

static void	step_y_axis(double *y, double dy, double angle)
{
	if (angle > 0 && angle < M_PI)
		*y -= dy;
	else if (angle > M_PI && angle < 2 * M_PI)
		*y += dy;
}

static void	dda_x_axis(t_ray *ray, t_cub3D *cub3d)
{
	double	dx;
	double	direction;

	direction = cos(ray->angle);
	if (direction == 0) // ray looking vertically
	{
		ray->distance = DBL_MAX;
		return ;
	}
	if (direction > 0) // ray looking right
		dx = MAP_CELL_SIZE - (abs((int32_t)ray->x_start) % MAP_CELL_SIZE);
	if (direction < 0) // ray looking left : this causes issues
		dx = abs((int32_t)ray->x_start) % MAP_CELL_SIZE + 1;
	while (is_valid_position(ray->x_end, ray->y_end, cub3d))
	{
		step_x_axis(&ray->x_end, dx, ray->angle);
		step_y_axis(&ray->y_end, dx * fabs(tan(ray->angle)), ray->angle);
		ray->distance += fabs(dx / direction);
		dx = MAP_CELL_SIZE;
	}
}

static void	dda_y_axis(t_ray *ray, t_cub3D *cub3d)
{
	double	dy;
	double	direction;

	direction = sin(ray->angle);
	if (direction == 0) // ray looking horizontally
	{
		ray->distance = DBL_MAX;
		return ;
	}
	if (direction > 0) // ray looking up : this causes issues
		dy = abs((int32_t)ray->y_start) % MAP_CELL_SIZE + 1;
	if (direction < 0) // ray looking down
		dy = MAP_CELL_SIZE - (abs((int32_t)ray->y_start) % MAP_CELL_SIZE);
	while (is_valid_position(ray->x_end, ray->y_end, cub3d))
	{
		step_y_axis(&ray->y_end, dy, ray->angle);
		step_x_axis(&ray->x_end, dy / fabs(tan(ray->angle)), ray->angle);
		ray->distance += fabs(dy / direction);
		dy = MAP_CELL_SIZE;
	}
}

static void	dda(t_ray *ray, t_cub3D *cub3d)
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

void	update_rays(t_cub3D *cub3d)
{
	t_ray	*ray;
	int32_t	i;

	i = 0;
	while (i <= WIDTH)
	{
		ray = cub3d->rays + i;
		ray->x_start = cub3d->player.x + MAP_PLAYER_SIZE / 2;
		ray->y_start = cub3d->player.y + MAP_PLAYER_SIZE / 2;
		ray->x_end = ray->x_start;
		ray->y_end = ray->y_start;
		ray->angle = cub3d->player.angle + FOV / 2 - i * (FOV / WIDTH);
		// if (ray->angle > (4 * M_PI / 6))
		// 	printf("ray->angle=%f\n", ray->angle * 180 / M_PI);
		if (ray->angle < 0)
			ray->angle += 2 * M_PI;
		if (ray->angle >= 2 * M_PI)
			ray->angle -= 2 * M_PI;
		ray->distance = 0;
		dda(ray, cub3d);
		// if (ray->angle == M_PI / 2)
		// 	printf("ray[%d]: x_start=%d, x_end=%d, y_start=%d, y_end=%d, distance=%f\n", i, ray->x_start, ray->x_end, ray->y_start, ray->y_end, ray->distance);
		i++;
	}
}
