/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:26:22 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/11 23:36:29 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Fill entire image with the specified color.
 *
 * @param image The pointer to MLX42 image
 * @param color The filling color
 *
 * @returns void
 */
void	fill(mlx_image_t *image, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}
