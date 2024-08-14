/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 00:13:38 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/14 11:55:06 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	copy_pixels(mlx_image_t *dest,mlx_image_t *src,int32_t offset)
{
	int32_t	x;
	int32_t	y;
	uint8_t	*d_pixels;
	uint8_t	*s_pixels;

	y = 0;
	while (y < offset)
	{
		x = 0;
		while (x < offset)
		{
			d_pixels = dest->pixels + (y * dest->width + x) * sizeof(uint32_t);
			s_pixels = src->pixels + (y * src->width + x) * sizeof(uint32_t);
			*((uint32_t *)d_pixels) = *((uint32_t *)s_pixels);
			x++;
		}
		y++;
	}
}
