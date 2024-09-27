/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:46:42 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 21:47:19 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_hooks(t_cub3D *cub3d)
{
	if (mlx_loop_hook(cub3d->mlx, loop_handler, cub3d) == false)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		destroy(cub3d);
		exit(1);
	}
	mlx_close_hook(cub3d->mlx, close_handler, cub3d);
}
