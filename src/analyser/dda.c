/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:57:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 15:19:00 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_hit(int32_t row, int32_t col, void *data)
{
	t_cub3D	*cub3d;

	cub3d = (t_cub3D *)data;
	if (row < 0 || (uint32_t)row >= cub3d->map->row_count)
		return (false);
	if (col < 0 || (uint32_t)col >= cub3d->map->col_count)
		return (false);
	if (
		cub3d->map->grid[row][col] == MAP_DOOR
		&& get_door(row, col, cub3d)->state != DOOR_OPEN
	)
		return (true);
	return (cub3d->map->grid[row][col] == MAP_WALL);
}

void	dda(t_ray *ray, t_cub3D *cub3d)
{
	find_hit_point(ray, cub3d, is_hit);
	set_end_point(ray->hit_row, ray->hit_col, ray);
	set_hit_texture(ray->hit_row, ray->hit_col, ray, cub3d);
	set_distance(ray, cub3d);
}
