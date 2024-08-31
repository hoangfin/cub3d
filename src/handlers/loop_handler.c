/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 00:13:59 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/29 16:51:56 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	loop_handler(void *param)
{
	t_cub3D	*cub3d;

	cub3d = (t_cub3D *)param;
	process_input(cub3d);
	update(cub3d, cub3d->mlx->delta_time);
	// handle_collisions(cub3d);
	update_ui(cub3d, cub3d->mlx->delta_time);
}
