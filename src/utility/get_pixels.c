/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 23:34:14 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 23:06:30 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"

/**
 * Return a pointer to pixel data at coordinate (x, y).
 */
uint8_t	*get_pixels(mlx_image_t *image, int32_t x, int32_t y)
{
	int32_t	offset;

	offset = (y * image->width + x) * sizeof(int32_t);
	return (image->pixels + offset);
}
