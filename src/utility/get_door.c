/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_door.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:32:01 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/19 22:47:39 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_door	*get_door(int32_t row, int32_t col, t_cub3D *cub3d)
{
	uint32_t	i;

	i = 0;
	while (i < cub3d->map->door_count)
	{
		if (
			(cub3d->doors[i].y / MAP_CELL_SIZE) == row
			&& (cub3d->doors[i].x / MAP_CELL_SIZE) == col
		)
			return (cub3d->doors + i);
		i++;
	}
	return (NULL);
}
