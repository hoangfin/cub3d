/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:08:54 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/27 16:56:22 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	delete_assets(t_cub3D *cub3d)
{
	int	i;

	i = 0;
	while (i < 4)
		mlx_delete_image(cub3d->mlx, cub3d->asset.walls[i++]);
	mlx_delete_image(cub3d->mlx, cub3d->asset.obstacle);
	mlx_delete_image(cub3d->mlx, cub3d->asset.navigator);
	delete_sprite(cub3d->asset.sprite_door, cub3d->mlx);
	delete_sprite(cub3d->asset.sprite_wand, cub3d->mlx);
}

static void	delete_images(t_cub3D *cub3d)
{
	mlx_delete_image(cub3d->mlx, cub3d->image.ceiling);
	mlx_delete_image(cub3d->mlx, cub3d->image.floor);
	mlx_delete_image(cub3d->mlx, cub3d->image.player);
	mlx_delete_image(cub3d->mlx, cub3d->image.scene);
	mlx_delete_image(cub3d->mlx, cub3d->image.minimap);
	mlx_delete_image(cub3d->mlx, cub3d->image.minimap_bg);
	mlx_delete_image(cub3d->mlx, cub3d->image.map);
}

void	destroy(t_cub3D *cub3d)
{
	if (cub3d->mlx != NULL)
		mlx_close_window(cub3d->mlx);
	delete_map(cub3d->map);
	delete_images(cub3d);
	delete_assets(cub3d);
	free(cub3d->rays);
	if (cub3d->mlx != NULL)
		mlx_terminate(cub3d->mlx);
}
