/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_character.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:36:08 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/08 23:08:29 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_character	*new_character(mlx_t *mlx, int32_t x, int32_t y, int32_t angle)
{
	t_character	*character;

	character = (t_character *)ft_calloc(1, sizeof(t_character));
	if (character == NULL)
		return (perror("new_character: ft_calloc"), NULL);
	character->image = mlx_new_image(mlx, RENDER_PIXELS, RENDER_PIXELS);
	if (character->image == NULL)
	{
		free(character);
		ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
		return (NULL);
	}
	character->x = x;
	character->y = y;
	character->angle = angle;
	// character->distance_moved = 0;
	// character->elapsed_time = 0;
	// character->current_frame = 0;
	// character->is_state_changed = false;
	character->state = PLAYER_IDLE;
	return (character);
}
