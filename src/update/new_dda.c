/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:30:04 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/10 15:05:58 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "cub3D.h"

static float	hitpoint_distance(float ax, float ay, float bx, float by, float angle) // returns distance between player and ray's end point
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}


void	dda(t_cub3D *cubed)
{
	t_ray	*ray;
	int	r, map_x, map_y, map_position, dof;
	float	ray_x, ray_y, x_offset, y_offset;
	float	aTan;
	float	nTan;
	int	i;
	float	hdist;
	float	vdist;
	float	hxpoint;
	float	hypoint;
	float	vxpoint;
	float	vypoint;

	while (i < WIDTH)
	{
		ray->angle = cubed->player.angle - FOV / 2 + i * FOV1;
		if (ray->angle < 0)
			ray->angle += 2 * M_PI;
		if (ray->angle > 2 * M_PI)
			ray->angle -= 2 * M_PI;
		
		dof = 0; // horizontal check
		hdist = 1000000;
		hxpoint = cubed->player.x;
		hypoint = cubed->player.y;
		aTan = -1 / tan(ray->angle);
		if (ray->angle == 0 || ray->angle == M_PI) // looking horizontally
		{
			ray_x = cubed->player.x;
			ray_y = cubed->player.y;
			dof = 8; // depth of field
		}
		else if (ray->angle > M_PI) // ray looking down
		{
			ray_y = (int)((cubed->player.y / MAP_CELL_SIZE) * MAP_CELL_SIZE) - 0.0001;
			ray_x = (cubed->player.y - ray_y) * aTan + cubed->player.x;
			y_offset = -MAP_CELL_SIZE;
			x_offset = -y_offset * aTan;
		}
		else if (ray->angle < M_PI) // ray looking up
		{
			ray_y = (int)((cubed->player.y / MAP_CELL_SIZE) * MAP_CELL_SIZE) + MAP_CELL_SIZE;
			ray_x = (cubed->player.y - ray_y) * aTan + cubed->player.x;
			y_offset = MAP_CELL_SIZE;
			x_offset = -y_offset * aTan;
		}
		while (dof < 8)
		{
			map_x = (int)(ray_x / MAP_CELL_SIZE);
			map_y = (int)(ray_y / MAP_CELL_SIZE);
			map_position = map_y * cubed->map->col_count + map_x; // looks for the position in map
			if (map_position < cubed->map->col_count * cubed->map->row_count && cubed->map->grid[map_position] == 1)
			{
				hxpoint = ray_x;
				hypoint = ray_y;
				hdist = hitpoint_distance(cubed->player.x + MAP_CELL_SIZE/2, cubed->player.y - MAP_CELL_SIZE / 2, hxpoint, hypoint, ray->angle);
				dof = 8;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				dof += 1;
			}
		}
		dof = 0; // vertical check
		vdist = 1000000;
		vxpoint = cubed->player.x;
		vypoint = cubed->player.y;
		nTan = -tan(ray->angle);
		if (ray->angle == M_PI / 2 || ray->angle == 3 * M_PI / 2) // looking vertically
		{
			ray_x = cubed->player.x;
			ray_y = cubed->player.y;
			dof = 8; // depth of field
		}
		else if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2) // ray looking left
		{
			ray_x = (int)((cubed->player.x / MAP_CELL_SIZE) * MAP_CELL_SIZE) - 0.0001;
			ray_y = (cubed->player.x - ray_x) * nTan + cubed->player.y;
			x_offset = -MAP_CELL_SIZE;
			y_offset = -x_offset * nTan;
		}
		else if (ray->angle < M_PI / 2 || ray->angle > 3 * M_PI / 2) // ray looking right
		{
			ray_x = (int)((cubed->player.x / MAP_CELL_SIZE) * MAP_CELL_SIZE) + MAP_CELL_SIZE;
			ray_y = (cubed->player.x - ray_x) * nTan + cubed->player.y;
			x_offset = MAP_CELL_SIZE;
			y_offset = -x_offset * nTan;
		}
		while (dof < 8)
		{
			map_x = (int)(ray_x / MAP_CELL_SIZE);
			map_y = (int)(ray_y / MAP_CELL_SIZE);
			map_position = map_y * cubed->map->col_count + map_x; // looks for the position in map
			if (map_position > 0 && map_position < cubed->map->col_count * cubed->map->row_count && cubed->map->grid[map_position] == 1)
			{
				vxpoint = ray_x;
				vypoint = ray_y;
				vdist = hitpoint_distance(cubed->player.x + MAP_CELL_SIZE/2, cubed->player.y - MAP_CELL_SIZE / 2, vxpoint, vypoint, ray->angle);
				dof = 8;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				dof += 1;
			}
		}
		if (vdist < hdist)
		{
			ray->x_end = vxpoint;
			ray->y_end = vypoint;
			ray->distance = vdist;
			ray->side = 1;
		}
		else
		{
			ray->x_end = hxpoint;
			ray->y_end = hypoint;
			ray->distance = hdist;
			ray->side = 0;
		}
		i++;
	}
}