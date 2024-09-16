/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:34:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/17 00:34:04 by hoatran          ###   ########.fr       */
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

	asset = &cub3d->asset;
	asset->obstacle = load_png(cub3d->mlx, "assets/textures/obstacle.png");
	asset->navigator = load_png(cub3d->mlx, "assets/textures/navigator.png");
	asset->walls[0] = load_png(cub3d->mlx, "assets/textures/north.png");
	asset->walls[1] = load_png(cub3d->mlx, "assets/textures/east.png");
	asset->walls[2] = load_png(cub3d->mlx, "assets/textures/south.png");
	asset->walls[3] = load_png(cub3d->mlx, "assets/textures/west.png");
	if (
		asset->obstacle == NULL
		|| asset->navigator == NULL
		|| asset->walls[0] == NULL
		|| asset->walls[1] == NULL
		|| asset->walls[2] == NULL
		|| asset->walls[3] == NULL
	)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(1);
	}
}

int	init(t_cub3D *cub3d, char *pathname)
{
	ft_bzero(cub3d, sizeof(t_cub3D));
	cub3d->map = load_map(pathname);
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
