/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:00:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 00:16:57 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

void	clear_pixels(
			uint8_t *start,
			uint32_t image_width,
			int32_t offset_x,
			int32_t offset_y
)
{
	int32_t		x;
	int32_t		y;
	uint32_t	*pixels;

	y = 0;
	while (y < offset_y)
	{
		x = 0;
		while (x < offset_x)
		{
			pixels = (uint32_t *)(start + (y * image_width + x) * 4);
			*pixels = 0;
			x++;
		}
		y++;
	}
}
