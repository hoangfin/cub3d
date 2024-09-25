/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_inputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:57:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 15:36:09 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	process_mouse_move(t_player_state *state, t_cub3D *cub3d)
{
	int32_t	last_mouse_x;

	last_mouse_x = cub3d->mouse_x;
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse_x, &cub3d->mouse_y);
	*state &= ~(PLAYER_TURNING_LEFT | PLAYER_TURNING_RIGHT);
	if (last_mouse_x < cub3d->mouse_x)
		*state |= PLAYER_TURNING_LEFT;
	if (last_mouse_x > cub3d->mouse_x)
		*state |= PLAYER_TURNING_RIGHT;
}

static void	process_keypress(t_player_state *state, mlx_t *mlx, t_cub3D *cub3d)
{
	*state &= ~(\
		PLAYER_MOVING_FORWARD \
		| PLAYER_MOVING_BACKWARD \
		| PLAYER_MOVING_LEFT \
		| PLAYER_MOVING_RIGHT \
	);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		destroy(cub3d);
		exit(EXIT_SUCCESS);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		*state |= PLAYER_MOVING_FORWARD;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		*state |= PLAYER_MOVING_BACKWARD;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		*state |= PLAYER_MOVING_LEFT;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		*state |= PLAYER_MOVING_RIGHT;
}

void	process_inputs(t_cub3D *cub3d)
{
	t_player_state	player_state;

	player_state = cub3d->player.state;
	process_mouse_move(&player_state, cub3d);
	if (mlx_is_mouse_down(cub3d->mlx, MLX_MOUSE_BUTTON_LEFT))
		player_state = PLAYER_ATTACKING;
	process_keypress(&player_state, cub3d->mlx, cub3d);
	transition_player(&cub3d->player, player_state);
}

