/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:10:15 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/22 19:53:52 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update(t_cub3D *cub3d, double elapsed_time)
{
	update_character(&cub3d->player, elapsed_time);
	update_doors(cub3d, elapsed_time);
}
