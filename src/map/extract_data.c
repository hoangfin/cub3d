/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:46:11 by emansoor          #+#    #+#             */
/*   Updated: 2024/08/19 13:39:27 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3D.h"

int	missing_map(t_map *map)
{
	if (
		map->wall_paths[0]
		&& map->wall_paths[1]
		&& map->wall_paths[2]
		&& map->wall_paths[3]
		&& map->color_ceiling
		&& map->color_floor
		&& !map->grid)
		return (1);
	return (0);
}

int	extract_data(t_map *map, char *data)
{
	//printf("current line: |%s|\n", data);
	if (get_texture(map, data) > 0 || get_color(map, data) > 0)
		return (1);
	return (0);
}
