/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_inputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:57:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/27 16:31:40 by hoatran          ###   ########.fr       */
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
/* 		| PLAYER_TURNING_LEFT \
		| PLAYER_TURNING_RIGHT \ */
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
/* 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		*state |= PLAYER_TURNING_RIGHT;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		*state |= PLAYER_TURNING_LEFT; */
}

static bool	is_hit(int32_t row, int32_t col, void *data)
{
	t_cub3D	*cub3d;

	cub3d = (t_cub3D *)data;
	if (row < 0 || (uint32_t)row >= cub3d->map->row_count)
		return (false);
	if (col < 0 || (uint32_t)col >= cub3d->map->col_count)
		return (false);
	if (cub3d->map->grid[row][col] == MAP_DOOR)
		return (true);
	return (cub3d->map->grid[row][col] == MAP_WALL);
}

void	process_inputs(t_cub3D *cub3d)
{
	t_player_state	player_state;
	t_ray			ray;
	t_door			*door;

	player_state = cub3d->player.state;
	process_mouse_move(&player_state, cub3d);
	if (mlx_is_mouse_down(cub3d->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		player_state = PLAYER_ATTACKING;
		init_ray(\
			&ray, \
			cub3d->player.x + MAP_PLAYER_SIZE / 2, \
			cub3d->player.y + MAP_PLAYER_SIZE / 2, \
			cub3d->player.angle \
		);
		find_hit_point(&ray, cub3d, is_hit);
		door = get_door(ray.hit_row, ray.hit_col, cub3d);
		if (door != NULL)
			transition_door(door, DOOR_CLOSING);
	}
	process_keypress(&player_state, cub3d->mlx, cub3d);
	transition_player(&cub3d->player, player_state);
}
