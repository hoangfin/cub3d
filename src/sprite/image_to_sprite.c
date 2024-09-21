/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_to_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:14:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/21 00:39:00 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int32_t	init_frames(t_sprite *sprite, mlx_image_t *image, mlx_t *mlx)
{
	uint8_t *const	original = image->pixels;
	uint32_t		row;
	uint32_t		col;

	row = 0;
	while (row < sprite->row_count)
	{
		col = 0;
		while (col < sprite->col_count)
		{
			sprite->frames[row][col] = mlx_new_image(
				mlx, sprite->frame_w, sprite->frame_h
			);
			if (sprite->frames[row][col] == NULL)
				return (-1);
			image->pixels = get_pixels(
				image, col * sprite->frame_w, row * sprite->frame_h
			);
			copy_pixels(
				sprite->frames[row][col], image, sprite->frame_w, sprite->frame_h
			);
			image->pixels = original;
			col++;
		}
		row++;
	}
	return (0);
}

static int32_t	create_frames(t_sprite *sprite)
{
	uint32_t	i;

	sprite->frames = (mlx_image_t ***)ft_calloc(
		sprite->row_count, sizeof(mlx_image_t **)
	);
	if (sprite->frames == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		return (-1);
	}
	i = 0;
	while (i < sprite->row_count)
	{
		sprite->frames[i] = (mlx_image_t **)ft_calloc(
			sprite->col_count, sizeof(mlx_image_t *)
		);
		if (sprite->frames[i] == NULL)
		{
			ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
			return (-1);
		}
		i++;
	}
	return (0);
}

t_sprite	*image_to_sprite(
				mlx_t *mlx,
				mlx_image_t *image,
				uint32_t row_count,
				uint32_t col_count
)
{
	t_sprite		*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		return (NULL);
	}
	sprite->row_count = row_count;
	sprite->col_count = col_count;
	sprite->frame_w = image->width / col_count;
	sprite->frame_h = image->height / row_count;
	if (create_frames(sprite) != 0 || init_frames(sprite, image, mlx) != 0)
	{
		delete_sprite(sprite, mlx);
		return (NULL);
	}
	return (sprite);
}
