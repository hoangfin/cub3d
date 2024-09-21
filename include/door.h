/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:56:04 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/22 00:37:06 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_H
# define DOOR_H

# include "MLX42.h"
# include "sprite.h"

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
	t_sprite		*sprite;
	t_door_state	state;
}	t_door;

void	transition_door(t_door *door, t_door_state state);
void	update_door(t_door *door, double elapsed_time);

#endif