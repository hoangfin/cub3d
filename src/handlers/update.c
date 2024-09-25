/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:10:15 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 16:49:08 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update(t_cub3D *cub3d, double elapsed_time)
{
	uint32_t	i;

	update_player(&cub3d->player, elapsed_time);
	i = 0;
	while (i < cub3d->map->door_count)
	{
		update_door(cub3d->doors + i, elapsed_time);
		i++;
	}
}
