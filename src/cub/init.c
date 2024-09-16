/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:34:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/16 11:39:06 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	create_rays(t_cub3D *cub3d)
{
	cub3d->rays = (t_ray *)ft_calloc(WIDTH, sizeof(t_ray));
	if (cub3d->rays == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		destroy(cub3d);
		exit(1);
	}
}

static void	load_assets(t_cub3D *cub3d)
{
	t_asset	*asset;
	int		wall;

	asset = &cub3d->asset;
	asset->obstacle = load_png(cub3d->mlx, "assets/textures/obstacle.png");
	asset->navigator = load_png(cub3d->mlx, "assets/textures/navigator.png");
	if (asset->obstacle == NULL || asset->navigator == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(1);
	}
	wall = 0;
	while (wall < 4)
	{
		asset->walls[wall] = load_png(cub3d->mlx, cub3d->map->wall_paths[wall]);
		if (asset->walls[wall] == NULL)
		{
			ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
			destroy(cub3d);
			exit(1);
		}
		wall++;
	}
}

int	init(t_cub3D *cub3d, char *pathname)
{
	ft_bzero(cub3d, sizeof(t_cub3D));
	cub3d->map = load_map(pathname);
	if (!cub3d->map)
	{
		delete_map(cub3d->map);
		return (free(cub3d), -1);
	}
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse_x, &cub3d->mouse_y);
	load_assets(cub3d);
	init_player(cub3d);
	create_rays(cub3d);
	create_images(cub3d);
	if (mlx_loop_hook(cub3d->mlx, loop_handler, cub3d) == false)
		return (destroy(cub3d), -1);
	mlx_close_hook(cub3d->mlx, close_handler, cub3d);
	return (0);
}
