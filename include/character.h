/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:33:27 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 13:35:13 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

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
	double				speed;
	double				angle;
	t_character_state	state;
	mlx_image_t			*image;
}	t_character;
