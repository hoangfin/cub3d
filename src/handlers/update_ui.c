/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:11:29 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 00:45:48 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "cub3D.h"

void	update_ui(t_cub3D *cub3d)
{
	clock_t	start;
	clock_t	end;

	start = clock();
	draw_map(cub3d->image.map, cub3d);
	end = clock();
	// printf("update_ui::draw_map runs in %f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000);

	draw_minimap(cub3d->image.minimap, cub3d);
	draw_player(cub3d);

	start = clock();
	draw_scene(cub3d);
	end = clock();
	printf("update_ui::draw_scene runs in %f ms\n", ((double)(end - start)) / CLOCKS_PER_SEC * 1000);
}
