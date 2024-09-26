/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:33:27 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 21:35:56 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include "MLX42.h"
# include "sprite.h"

typedef enum e_player_state
{
	PLAYER_IDLE = 0,
	PLAYER_MOVING_FORWARD = 1 << 0,
	PLAYER_MOVING_RIGHT = 1 << 1,
	PLAYER_MOVING_BACKWARD = 1 << 2,
	PLAYER_MOVING_LEFT = 1 << 3,
	PLAYER_TURNING_LEFT = 1 << 4,
	PLAYER_TURNING_RIGHT = 1 << 5,
	PLAYER_ATTACKING = 1 << 6,
	PLAYER_DIED = 1 << 7
}	t_player_state;

typedef struct s_player
{
	double			x;
	double			y;
	double			prev_x;
	double			prev_y;
	double			elapsed_time;
	double			speed;
	double			angle;
	int32_t			frame_index;
	t_sprite		*sprite;
	t_player_state	state;
}	t_player;

void	transition_player(t_player *player, t_player_state state);
void	update_player(t_player *player, double elapsed_time);

#endif
