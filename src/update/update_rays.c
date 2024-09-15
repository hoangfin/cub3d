/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:47:12 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/15 14:20:45 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "cub3D.h"

void	update_rays(t_cub3D *cub3d)
{
	t_ray	*ray;
	int32_t	i;

	i = 0;
	clock_t start_time = clock();
	while (i < WIDTH)
	{
		ray = cub3d->rays + i;
		ray->x_start = cub3d->player.x + MAP_PLAYER_SIZE / 2;
		ray->y_start = cub3d->player.y + MAP_PLAYER_SIZE / 2;
		ray->x_end = ray->x_start;
		ray->y_end = ray->y_start;
		ray->distance = 0;
		ray->angle = cub3d->player.angle + FOV / 2 - i * FOV / (WIDTH - 1);
		if (ray->angle < 0)
			ray->angle += 2 * M_PI;
		if (ray->angle >= 2 * M_PI)
			ray->angle -= 2 * M_PI;
		ray->dir_x = cos(ray->angle);
		ray->dir_y = sin(ray->angle);
		ray->hit_side = -1;
		dda(ray, cub3d);
		i++;
	}
    clock_t end_time = clock();
	double time_spent = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;
    printf("update_rays::execution time: %f ms\n", time_spent);
}
