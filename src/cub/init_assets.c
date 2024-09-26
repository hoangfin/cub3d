/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:21:48 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 22:28:00 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_assets(t_cub3D *cub3d)
{
	t_asset	*a;

	a = &cub3d->asset;
	a->obstacle = load_png(cub3d->mlx, "assets/textures/obstacle.png");
	a->navigator = load_png(cub3d->mlx, "assets/textures/navigator.png");
	a->sprite_door = load_sprite(cub3d->mlx, "assets/sprites/door.png", 1, 14);
	a->sprite_wand = load_sprite(cub3d->mlx, "assets/sprites/wand.png", 1, 9);
	a->walls[0] = load_png(cub3d->mlx, cub3d->map->wall_paths[0]);
	a->walls[1] = load_png(cub3d->mlx, cub3d->map->wall_paths[1]);
	a->walls[2] = load_png(cub3d->mlx, cub3d->map->wall_paths[2]);
	a->walls[3] = load_png(cub3d->mlx, cub3d->map->wall_paths[3]);
	if (
		a->obstacle == NULL || a->navigator == NULL || a->sprite_door == NULL
		|| a->sprite_wand == NULL || a->walls[0] == NULL || a->walls[1] == NULL
		|| a->walls[2] == NULL || a->walls[3] == NULL
	)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(1);
	}
}
