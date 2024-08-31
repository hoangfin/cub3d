/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_character.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 23:36:08 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/24 23:28:25 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "cub3D.h"

t_character	*new_character(int32_t x, int32_t y, double speed, double angle)
{
	t_character	*character;

	character = (t_character *)malloc(sizeof(t_character));
	if (character == NULL)
	{
		ft_fprintf(2, "Error\n%s\n", strerror(errno));
		return (NULL);
	}
	character->x = x;
	character->y = y;
	character->speed = speed;
	character->angle = angle;
	character->state = CHAR_IDLE;
	return (character);
}
