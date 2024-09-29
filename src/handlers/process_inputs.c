/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_inputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:57:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/29 13:17:15 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static void	process_mouse_move(t_player_state *state, t_cub3D *cub3d)
{
	int32_t	last_mouse_x;

	last_mouse_x = cub3d->mouse_x;
	mlx_get_mouse_pos(cub3d->mlx, &cub3d->mouse_x, &cub3d->mouse_y);
	if (last_mouse_x < cub3d->mouse_x)
		*state |= PLAYER_TURNING_LEFT;
	if (last_mouse_x > cub3d->mouse_x)
		*state |= PLAYER_TURNING_RIGHT;
}

static void	process_mouse_press(
	t_player_state *state,
	int32_t x,
	int32_t y,
	t_cub3D *cub3d
)
{
	t_ray	ray;
	t_door	*door;

	if (mlx_is_mouse_down(cub3d->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		*state = PLAYER_ATTACKING;
		init_ray(\
			&ray, \
			cub3d->player.x + MAP_PLAYER_SIZE / 2, \
			cub3d->player.y + MAP_PLAYER_SIZE / 2, \
			cub3d->player.angle \
		);
		find_hit_point(&ray, cub3d, is_hit);
		door = get_door(ray.hit_row, ray.hit_col, cub3d);
		if (
			door != NULL
			&& !is_door(x, y, cub3d)
			&& !is_door(x + MAP_PLAYER_SIZE, y, cub3d)
			&& !is_door(x, y + MAP_PLAYER_SIZE, cub3d)
			&& !is_door(x + MAP_PLAYER_SIZE, y + MAP_PLAYER_SIZE, cub3d)
		)
			transition_door(door, DOOR_CLOSING);
	}
}

static void	process_keypress(t_player_state *state, mlx_t *mlx, t_cub3D *cub3d)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		destroy(cub3d);
		exit(EXIT_SUCCESS);
	}
	if (*state == PLAYER_ATTACKING)
		return ;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		*state |= PLAYER_MOVING_FORWARD;
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		*state |= PLAYER_MOVING_BACKWARD;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		*state |= PLAYER_MOVING_LEFT;
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		*state |= PLAYER_MOVING_RIGHT;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		*state |= PLAYER_TURNING_RIGHT;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		*state |= PLAYER_TURNING_LEFT;
}

void	process_inputs(t_cub3D *cub3d)
{
	t_player_state	state;

	state = PLAYER_IDLE;
	process_mouse_move(&state, cub3d);
	process_mouse_press(&state, cub3d->player.x, cub3d->player.y, cub3d);
	process_keypress(&state, cub3d->mlx, cub3d);
	transition_player(&cub3d->player, state);
}
