/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_doors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:32:19 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 14:18:43 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_doors(t_cub3D *cub3d, double elapsed_time)
{
	uint32_t	i;

	i = 0;
	while (i < cub3d->map->door_count)
	{
		transition_door(cub3d->doors + i, DOOR_OPENING);
		update_door(cub3d->doors + i, elapsed_time);
		i++;
	}
}
