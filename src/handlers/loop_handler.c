/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:13:59 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 00:44:48 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "cub3D.h"

static void	update_rays(t_cub3D *cub3d)
{
	t_ray	*ray;
	int32_t	i;

	i = 0;
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
}

void	loop_handler(void *param)
{
	t_cub3D	*cub3d;
	clock_t	start;
	clock_t	end;

	start = clock();

	cub3d = (t_cub3D *)param;
	process_inputs(cub3d);

	// start = clock();
	update(cub3d, cub3d->mlx->delta_time);
	// end = clock();
	// printf("loop_handler::update runs in %f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000);

	handle_collisions(cub3d);
	update_rays(cub3d);

	// start = clock();
	update_ui(cub3d);
	end = clock();
	// printf("loop_handler::update_ui runs in %f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000);
	printf("loop_handler runs in %f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000);

}
