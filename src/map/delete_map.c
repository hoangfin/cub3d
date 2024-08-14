/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:33:21 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/14 08:00:17 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	delete_map(mlx_t *mlx, t_map *map, char *str) // update prototype in main
{
	if (str)
		free(str);
	if (map->grid)
		ft_matrix_delete(&map->grid);
	if (map->north_wall)
		mlx_delete_image(mlx, map->north_wall);
	if (map->south_wall)
		mlx_delete_image(mlx, map->south_wall);
	if (map->east_wall)
		mlx_delete_image(mlx, map->east_wall);
	if (map->west_wall)
		mlx_delete_image(mlx, map->west_wall);
}
