/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:34:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/26 21:52:53 by hoatran          ###   ########.fr       */
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

void	init(t_cub3D *cub3d, char *pathname)
{
	cub3d->map = load_map(pathname);
	if (cub3d->map == NULL)
	{
		delete_map(cub3d->map);
		exit(1);
	}
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (cub3d->mlx == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(1);
	}
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse_x, &cub3d->mouse_y);
	init_assets(cub3d);
	init_player(cub3d);
	init_doors(cub3d);
	init_rays(cub3d);
	init_images(cub3d);
	init_hooks(cub3d);
	render_images(cub3d);
}
