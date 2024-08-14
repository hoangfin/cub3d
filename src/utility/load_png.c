/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_png.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 11:54:44 by hoatran           #+#    #+#             */
/*   Updated: 2024/08/11 16:06:22 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Load `.png` image from a path into MLX42 image.
 *
 * @param mlx The pointer to MLX42 instance
 * @param pathname The file path to texture image
 *
 * @returns Pointer to MLX42 image or NULL on failure
 */
mlx_image_t	*load_png(mlx_t *mlx, const char *pathname)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(pathname);
	if (texture == NULL)
		return (NULL);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}
