/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_inputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:57:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 17:21:15 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	process_mouse_move(t_character_state *state, t_cub3D *cub3d)
{
	int32_t	last_mouse_x;

	last_mouse_x = cub3d->mouse_x;
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse_x, &cub3d->mouse_y);
	*state &= ~(CHAR_TURNING_LEFT | CHAR_TURNING_RIGHT);
	if (last_mouse_x < cub3d->mouse_x)
		*state |= CHAR_TURNING_LEFT;
	if (last_mouse_x > cub3d->mouse_x)
		*state |= CHAR_TURNING_RIGHT;
}

static void	process_keypress(t_character_state *state, mlx_t *mlx)
{
	*state &= ~(\
		CHAR_MOVING_FORWARD \
		| CHAR_MOVING_BACKWARD \
		| CHAR_MOVING_LEFT \
		| CHAR_MOVING_RIGHT \
	);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		*state |= CHAR_MOVING_FORWARD;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		*state |= CHAR_MOVING_BACKWARD;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		*state |= CHAR_MOVING_LEFT;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		*state |= CHAR_MOVING_RIGHT;
}

void	process_inputs(t_cub3D *cub3d)
{
	t_character_state	player_state;

	player_state = cub3d->player.state;
	process_mouse_move(&player_state, cub3d);
	if (mlx_is_key_down(cub3d->mlx, MLX_KEY_P))
	// if (mlx_is_mouse_down(cub3d->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		printf("You've clicked left mouse\n");
		player_state = CHAR_ATTACKING;
	}
	process_keypress(&player_state, cub3d->mlx);
	transition_character(&cub3d->player, player_state);
}

