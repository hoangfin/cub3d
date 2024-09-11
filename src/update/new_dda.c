/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:30:04 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/11 12:25:38 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

		/* map_x = (int)(ray->x_end / MAP_CELL_SIZE);
		map_y = (int)(ray->y_end / MAP_CELL_SIZE);
		map_position = map_y * cub3d->map->col_count + map_x; // looks for the position in map
		if (map_position < cub3d->map->col_count * cub3d->map->row_count && cub3d->map->grid[map_position] == 1)
		{
			ray->distance = hitpoint_distance(ray->x_start, ray->y_start, ray->x_end, ray->y_end);
			dof = 8;
		} */

static float	hitpoint_distance(float ax, float ay, float bx, float by) // returns distance between player and ray's end point
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

static void	find_hitpoint(t_ray *ray, t_cub3D *cub3d, float x_offset, float y_offset)
{
	unsigned int	dof;
	unsigned int	max;

	max = 0;
	dof = 0;
	if (cub3d->map->col_count > cub3d->map->row_count)
		max = cub3d->map->row_count;
	else
		max = cub3d->map->col_count;
	while (dof < 4)
	{
		if (is_valid_position(ray->x_end, ray->y_end, cub3d) == false)
		{
			ray->distance = hitpoint_distance(ray->x_start, ray->y_start, ray->x_end, ray->y_end);
			dof = 4;
		}
		else
		{
			ray->x_end += x_offset;
			ray->y_end += y_offset;
			dof += 1;
		}
	}
}

static void	dda_horizontal(t_ray *ray, t_cub3D *cub3d)
{
	float	aTan;
	float	x_offset;
	float	y_offset;
	
	aTan = -1 / tan(ray->angle);
	if (ray->angle == 0 || ray->angle == M_PI) // looking horizontally
	{}
	else if (ray->angle > M_PI) // ray looking down
	{
		ray->y_end = (int)((ray->y_start / MAP_CELL_SIZE) * MAP_CELL_SIZE) - 0.0001;
		ray->x_end = (ray->y_start - ray->y_end) * aTan + ray->x_start;
		y_offset = -MAP_CELL_SIZE;
		x_offset = -y_offset * aTan;
		find_hitpoint(ray, cub3d, x_offset, y_offset);
	}
	else if (ray->angle < M_PI) // ray looking up
	{
		ray->y_end = (int)((ray->y_start / MAP_CELL_SIZE) * MAP_CELL_SIZE) + MAP_CELL_SIZE;
		ray->x_end = (ray->y_start - ray->y_end) * aTan + ray->x_start;
		y_offset = MAP_CELL_SIZE;
		x_offset = -y_offset * aTan;
		find_hitpoint(ray, cub3d, x_offset, y_offset);
	}
}

static void	dda_vertical(t_ray *ray, t_cub3D *cub3d)
{
	float	nTan;
	float	x_offset;
	float	y_offset;

	nTan = -tan(ray->angle);
	if (ray->angle == M_PI / 2 || ray->angle == 3 * M_PI / 2) // looking vertically
	{}
	else if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2) // ray looking left
	{
		ray->x_end = (int)((ray->x_start / MAP_CELL_SIZE) * MAP_CELL_SIZE) - 0.0001;
		ray->y_end = (ray->x_start - ray->x_end) * nTan + ray->y_start;
		x_offset = -MAP_CELL_SIZE;
		y_offset = -x_offset * nTan;
		find_hitpoint(ray, cub3d, x_offset, y_offset);
	}
	else if (ray->angle < M_PI / 2 || ray->angle > 3 * M_PI / 2) // ray looking right
	{
		ray->x_end = (int)((ray->x_start / MAP_CELL_SIZE) * MAP_CELL_SIZE) + MAP_CELL_SIZE;
		ray->y_end = (ray->x_start - ray->x_end) * nTan + ray->y_start;
		x_offset = MAP_CELL_SIZE;
		y_offset = -x_offset * nTan;
		find_hitpoint(ray, cub3d, x_offset, y_offset);
	}
}

static void	dda(t_ray *ray, t_cub3D *cub3d)
{
	t_ray	ray_h;
	t_ray	ray_v;

	ray_h = *ray;
	ray_v = *ray;
	dda_horizontal(&ray_h, cub3d);
	dda_vertical(&ray_v, cub3d);
	if (ray_h.distance < ray_v.distance)
	{
		ray_h.side = 0;
		*ray = ray_h;
	}
	else
	{
		ray_v.side = 1;
		*ray = ray_v;
	}
}

void	update_rays(t_cub3D *cub3d)
{
	t_ray			*ray;
	unsigned int	index;

	index = 0;
	while (index < WIDTH)
	{
		ray = cub3d->rays + index;
		ray->angle = cub3d->player.angle - FOV / 2 + index * (FOV / WIDTH);
		if (ray->angle < 0)
			ray->angle += 2 * M_PI;
		if (ray->angle > 2 * M_PI)
			ray->angle -= 2 * M_PI;
		ray->distance = 0; //hdist | vdist
		ray->distance_x = 0; // hxpoint | vxpoint
		ray->distance_y = 0; // hypoint | vypoint
		ray->x_start = cub3d->player.x + MAP_CELL_SIZE / 2;
		ray->y_start = cub3d->player.y + MAP_CELL_SIZE / 2;
		ray->x_end = ray->x_start;
		ray->y_end = ray->y_start;
		dda(ray, cub3d);
		index++;
	}
}
