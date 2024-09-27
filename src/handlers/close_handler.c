/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:35:42 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/27 16:43:04 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	close_handler(void	*param)
{
	t_cub3D	*cub3d;

	cub3d = (t_cub3D *)param;
	destroy(cub3d);
	exit(EXIT_SUCCESS);
}
