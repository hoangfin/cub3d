/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:04 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 14:49:47 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPEN,
	DOOR_CLOSING,
	DOOR_OPENING
}	t_door_state;

typedef struct s_door
{
	int32_t			x;
	int32_t			y;
	double			elapsed_time;
	mlx_image_t		*image;
	t_door_state	state;
}	t_door;

void	transition_door(t_door *door, t_door_state state);
