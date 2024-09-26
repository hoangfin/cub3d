/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:34:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/26 15:00:06 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_rays(t_cub3D *cub3d)
{
	cub3d->rays = (t_ray *)ft_calloc(WIDTH, sizeof(t_ray));
	if (cub3d->rays == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		destroy(cub3d);
		exit(1);
	}
}

static void	init_asset(t_cub3D *cub3d)
{
	t_asset		*asset;

	asset = &cub3d->asset;
	asset->obstacle = load_png(cub3d->mlx, "assets/textures/obstacle.png");
	asset->navigator = load_png(cub3d->mlx, "assets/textures/navigator.png");
	asset->sprite_door = load_sprite(cub3d->mlx, "assets/sprites/door.png", 1, 14);
	asset->sprite_wand = load_sprite(cub3d->mlx, "assets/sprites/wand.png", 1, 9);
	asset->walls[0] = load_png(cub3d->mlx, cub3d->map->wall_paths[0]);
	asset->walls[1] = load_png(cub3d->mlx, cub3d->map->wall_paths[1]);
	asset->walls[2] = load_png(cub3d->mlx, cub3d->map->wall_paths[2]);
	asset->walls[3] = load_png(cub3d->mlx, cub3d->map->wall_paths[3]);
	if (
		asset->obstacle == NULL || asset->navigator == NULL
		|| asset->sprite_door == NULL || asset->sprite_wand == NULL
		|| asset->walls[0] == NULL || asset->walls[1] == NULL
		|| asset->walls[2] == NULL || asset->walls[3] == NULL
	)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(1);
	}
}

void	init(t_cub3D *cub3d, char *pathname)
{
	cub3d->map = load_map(pathname);
	if (cub3d->map == NULL)
	{
		delete_map(cub3d->map);
		exit(1);
	}
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse_x, &cub3d->mouse_y);
	init_asset(cub3d);
	init_player(cub3d);
	init_doors(cub3d);
	init_rays(cub3d);
	create_images(cub3d);
	if (mlx_loop_hook(cub3d->mlx, loop_handler, cub3d) == false)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(1);
	}
	mlx_close_hook(cub3d->mlx, close_handler, cub3d);
}
