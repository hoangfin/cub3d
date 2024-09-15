/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:57:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/15 17:23:54 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda(t_ray *ray, t_cub3D *cub3d)
{
	int32_t	row;
	int32_t	col;

	row = ray->y_start / MAP_CELL_SIZE;
	col = ray->x_start / MAP_CELL_SIZE;
	dda_find_ray_hit_point(&row, &col, ray, cub3d);
	dda_set_ray_end_point(row, col, ray, cub3d);
	dda_set_ray_distance(ray, cub3d);
}
