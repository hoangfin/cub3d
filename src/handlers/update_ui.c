/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:11:29 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/09 16:40:28 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_ui(t_cub3D *cub3d, double elapsed_time)
{
	(void)elapsed_time;
	draw_map(cub3d->image.map, cub3d);
	draw_minimap(cub3d->image.minimap, cub3d);
	draw_scene(cub3d);
}
