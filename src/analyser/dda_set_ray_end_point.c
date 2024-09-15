/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_set_ray_end_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 21:55:20 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/15 20:44:50 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda_set_ray_end_point(
	int32_t row_hit,
	int32_t col_hit,
	t_ray *ray,
	t_cub3D *cub3d
)
{
	double	displacement;

	(void)cub3d;
	if (ray->hit_side == 0)
	{
		ray->x_end = col_hit * MAP_CELL_SIZE;
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
		ray->y_end = row_hit * MAP_CELL_SIZE;
		if (ray->y_end < ray->y_start)
			ray->y_end += MAP_CELL_SIZE;
		displacement = fabs((ray->y_end - ray->y_start) / tan(ray->angle));
		if (ray->dir_x > 0)
			ray->x_end = ray->x_start + displacement;
		else
			ray->x_end = ray->x_start - displacement;
	}
}
