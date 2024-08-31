/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:10:15 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/31 14:35:54 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update(t_cub3D *cub3d, double elapsed_time)
{
	update_player(cub3d, elapsed_time);
	// update_minimap(cub3D);
}
