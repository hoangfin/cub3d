/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:39:03 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 15:15:30 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ray.h"

void	init_ray(t_ray *ray, int32_t x, int32_t y, double angle)
{
	ray->x_start = x;
	ray->y_start = y;
	ray->x_end = ray->x_start;
	ray->y_end = ray->y_start;
	ray->angle = angle;
	if (angle < 0)
		ray->angle += 2 * M_PI;
	if (angle >= 2 * M_PI)
		ray->angle -= 2 * M_PI;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	ray->hit_row = -1;
	ray->hit_col = -1;
	ray->hit_side = -1;
	ray->distance = 0;
}
