/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_end_point.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:55:20 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/24 10:27:31 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	handle_horizontal_hit(int32_t col, t_ray *ray)
{
	double	dy;

	ray->x_end = col * MAP_CELL_SIZE;
	if (ray->x_end < ray->x_start)
		ray->x_end += MAP_CELL_SIZE;
	dy = fabs((ray->x_end - ray->x_start) * ray->dir_y / ray->dir_x);
	if (ray->dir_y > 0)
		ray->y_end = ray->y_start - dy;
	else
		ray->y_end = ray->y_start + dy;
}

static void	handle_vertical_hit(int32_t row, t_ray *ray)
{
	double	dx;

	ray->y_end = row * MAP_CELL_SIZE;
	if (ray->y_end < ray->y_start)
		ray->y_end += MAP_CELL_SIZE;
	dx = fabs((ray->y_end - ray->y_start) * ray->dir_x / ray->dir_y);
	if (ray->dir_x > 0)
		ray->x_end = ray->x_start + dx;
	else
		ray->x_end = ray->x_start - dx;
}

void	set_end_point(int32_t row, int32_t col, t_ray *ray)
{
	if (ray->hit_side == 0)
		handle_horizontal_hit(col, ray);
	else
		handle_vertical_hit(row, ray);
}
