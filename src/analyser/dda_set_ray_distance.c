/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_set_ray_distance.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:56:56 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/15 13:12:01 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	calc_perp_distance(double distance, double angle_diff)
{
	double	cos_value;

	if (angle_diff < 0)
		angle_diff += 2 * M_PI;
	if (angle_diff >= 2 * M_PI)
		angle_diff -= 2 * M_PI;
	cos_value = cos(angle_diff);
	return (distance * fabs(cos_value));
}

void	dda_set_ray_distance(t_ray *ray, t_cub3D *cub3d)
{
	double	distance;
	double	angle_diff;

	angle_diff = cub3d->player.angle - ray->angle;
	if (is_equal(ray->dir_x, 0.0))
		distance = fabs((ray->y_end - ray->y_start) / ray->dir_y);
	else
		distance = fabs((ray->x_end - ray->x_start) / ray->dir_x);
	ray->distance = calc_perp_distance(distance, angle_diff);
}
