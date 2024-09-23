/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 00:13:38 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 23:06:30 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

void	copy_pixels(
	mlx_image_t *dest,
	mlx_image_t *src,
	int32_t offset_x,
	int32_t offset_y
)
{
	int32_t		x;
	int32_t		y;
	uint32_t	*dest_pixels;
	uint32_t	*src_pixels;

	y = 0;
	while (y < offset_y)
	{
		x = 0;
		while (x < offset_x)
		{
			dest_pixels = (uint32_t *)get_pixels(dest, x, y);
			src_pixels = (uint32_t *)get_pixels(src, x, y);
			*dest_pixels = *src_pixels;
			x++;
		}
		y++;
	}
}
