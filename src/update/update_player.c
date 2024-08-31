/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:10:09 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/31 14:12:27 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_player_angle(t_character *player)
{
	if (!(player->state & (CHAR_TURNING_LEFT | CHAR_TURNING_RIGHT)))
		return ;
	if (player->state & CHAR_TURNING_LEFT)
		player->angle -= M_PI / 36;
	if (player->state & CHAR_TURNING_RIGHT)
		player->angle += M_PI / 36;
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	if (player->angle >= 2 * M_PI)
		player->angle -= 2 * M_PI;
}

static void	get_displacement(
	double *dx,
	double *dy,
	double distance,
	t_character *player
)
{
	double	displacement_angle;

	displacement_angle = player->angle;
	if (player->state & CHAR_MOVING_BACKWARD)
		displacement_angle += M_PI;
	else if (player->state & CHAR_MOVING_LEFT)
		displacement_angle += M_PI / 2;
	else if (player->state & CHAR_MOVING_RIGHT)
		displacement_angle += 3 * M_PI / 2;
	*dx = distance * cos(displacement_angle);
	*dy = distance * sin(displacement_angle);
}

void	update_player(t_cub3D *cub3d, double elapsed_time)
{
	t_character_state	char_moving_mask;
	double				distance;
	double				dx;
	double				dy;

	set_player_angle(&cub3d->player);
	char_moving_mask = (\
		CHAR_MOVING_FORWARD \
		| CHAR_MOVING_BACKWARD \
		| CHAR_MOVING_LEFT \
		| CHAR_MOVING_RIGHT \
	);
	distance = 0.0;
	if (cub3d->player.state & char_moving_mask)
		distance = cub3d->player.speed * elapsed_time;
	get_displacement(&dx, &dy, distance, &cub3d->player);
	set_character_pos(cub3d->player.x + dx, cub3d->player.y - dy, cub3d);
}
