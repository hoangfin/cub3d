/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:34:37 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/14 14:36:39 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3D.h"

static int	init_player(t_cub3D *cub)
{
	cub->player = ft_calloc(1, sizeof(t_character));
	if (cub->player == NULL)
		return (-1);
	return (0);
}

// static int	init_rays(t_cub3D *cub3D)
// {
// 	int	i;

// 	cub3D->ray_count = cub3D->map->width
// 	cub3D->rays = (t_ray *)malloc(cub3D->ray_count * sizeof(t_ray));
// 	if (cub3D->rays == NULL)
// 		return (-1);
// 	i = 0;
// 	while (i < cub3D->ray_count)
// 	{
// 		cub3D->rays[i].start_x = cub3D->player->x;
// 		cub3D->rays[i].start_y = cub3D->player->y;
// 		// cub3D->rays[i].end_x = cub3D->player->x;
// 		// cub3D->rays[i].end_y = cub3D->player->y;
// 		// cub3D->rays[i].length = sqrt();
// 		i++;
// 	}
// 	return (0);
// }

int	init(t_cub3D *cub3D, const char *pathname)
{
	ft_bzero(cub3D, sizeof(t_cub3D));
	cub3D->mlx = mlx_init(800, 600, "cub3D", false);
	cub3D->map = load_map(pathname);
	if (cub3D->map == NULL)
		return (destroy(cub3D), -1);
	// if (init_rays(cub3D) != 0)
	// 	return (destroy(cub3D), -1);
	if (init_player(cub3D) != 0)
		return (destroy(cub3D), -1);
	return (0);
}
