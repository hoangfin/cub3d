/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:33:27 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 16:43:23 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_H
# define CHARACTER_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include "MLX42.h"
# include "sprite.h"

typedef enum e_character_state
{
	CHAR_IDLE = 0,
	CHAR_MOVING_FORWARD = 1 << 0,
	CHAR_MOVING_RIGHT = 1 << 1,
	CHAR_MOVING_BACKWARD = 1 << 2,
	CHAR_MOVING_LEFT = 1 << 3,
	CHAR_TURNING_LEFT = 1 << 4,
	CHAR_TURNING_RIGHT = 1 << 5,
	CHAR_ATTACKING = 1 << 6,
	CHAR_DIED = 1 << 7
}	t_character_state;

typedef struct s_character
{
	double				x;
	double				y;
	double				prev_x;
	double				prev_y;
	double				elapsed_time;
	double				speed;
	double				angle;
	mlx_image_t			*image;
	t_sprite			*sprite;
	t_character_state	state;
}	t_character;

void	transition_character(t_character *character, t_character_state state);
void	update_character(t_character *character, double elapsed_time);

#endif
