/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:57:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/06 00:41:20 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	process_mouse_move(t_cub3D *cub3D)
{
	int32_t	last_mouse_x;

	last_mouse_x = cub3D->mouse_x;
	mlx_get_mouse_pos(cub3D->mlx, &cub3D->mouse_x, &cub3D->mouse_y);
	cub3D->player.state &= ~(CHAR_TURNING_LEFT | CHAR_TURNING_RIGHT);
	if (last_mouse_x < cub3D->mouse_x)
		cub3D->player.state |= CHAR_TURNING_LEFT;
	if (last_mouse_x > cub3D->mouse_x)
		cub3D->player.state |= CHAR_TURNING_RIGHT;
}

static void	process_keypress(t_cub3D *cub3D)
{
	cub3D->player.state &= ~(\
		CHAR_MOVING_FORWARD \
		| CHAR_MOVING_BACKWARD \
		| CHAR_MOVING_LEFT \
		| CHAR_MOVING_RIGHT \
	);
	if (mlx_is_key_down(cub3D->mlx, MLX_KEY_W))
		cub3D->player.state |= CHAR_MOVING_FORWARD;
	if (mlx_is_key_down(cub3D->mlx, MLX_KEY_S))
		cub3D->player.state |= CHAR_MOVING_BACKWARD;
	if (mlx_is_key_down(cub3D->mlx, MLX_KEY_A))
		cub3D->player.state |= CHAR_MOVING_LEFT;
	if (mlx_is_key_down(cub3D->mlx, MLX_KEY_D))
		cub3D->player.state |= CHAR_MOVING_RIGHT;
}

void	process_input(t_cub3D *cub3D)
{
	process_mouse_move(cub3D);
	process_keypress(cub3D);
}

