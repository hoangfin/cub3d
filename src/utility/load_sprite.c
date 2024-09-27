/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:14:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/27 15:01:28 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "utility.h"

static int32_t	init_frames(t_sprite *sprite, mlx_image_t *image, mlx_t *mlx)
{
	uint8_t *const	original = image->pixels;
	const uint32_t	frame_w = sprite->frame_w;
	const uint32_t	frame_h = sprite->frame_h;
	uint32_t		row;
	uint32_t		col;

	row = 0;
	while (row < sprite->row_count)
	{
		col = 0;
		while (col < sprite->col_count)
		{
			sprite->frames[row][col] = mlx_new_image(mlx, frame_w, frame_h);
			if (sprite->frames[row][col] == NULL)
				return (
					ft_fprintf(2, "Error\n%s\n", mlx_strerror(mlx_errno)), -1);
			image->pixels = get_pixels(image, col * frame_w, row * frame_h);
			copy_pixels(sprite->frames[row][col], image, frame_w, frame_h);
			image->pixels = original;
			col++;
		}
		row++;
	}
	return (0);
}

static int	init_sprite(
	t_sprite *sprite,
	uint32_t row_count,
	uint32_t col_count,
	mlx_image_t *image
)
{
	uint32_t	i;

	sprite->row_count = row_count;
	sprite->col_count = col_count;
	sprite->frame_w = image->width / col_count;
	sprite->frame_h = image->height / row_count;
	sprite->frames = ft_calloc(sprite->row_count, sizeof(mlx_image_t **));
	if (sprite->frames == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		return (-1);
	}
	i = 0;
	while (i < sprite->row_count)
	{
		sprite->frames[i] = ft_calloc(sprite->col_count, sizeof(mlx_image_t *));
		if (sprite->frames[i] == NULL)
		{
			ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
			return (-1);
		}
		i++;
	}
	return (0);
}

static t_sprite	*new_sprite(mlx_t *mlx, const char *pathname, mlx_image_t **img)
{
	t_sprite	*sprite;

	*img = load_png(mlx, pathname);
	if (*img == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", mlx_strerror(mlx_errno));
		return (NULL);
	}
	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (sprite == NULL)
	{
		mlx_delete_image(mlx, *img);
		ft_fprintf(STDERR_FILENO, "Error\n%s\n", strerror(errno));
		return (NULL);
	}
	return (sprite);
}

t_sprite	*load_sprite(
	mlx_t *mlx,
	const char *pathname,
	uint32_t row_count,
	uint32_t col_count
)
{
	mlx_image_t	*image;
	t_sprite	*sprite;

	sprite = new_sprite(mlx, pathname, &image);
	if (sprite == NULL)
		return (NULL);
	if (
		init_sprite(sprite, row_count, col_count, image) != 0
		|| init_frames(sprite, image, mlx) != 0
	)
	{
		mlx_delete_image(mlx, image);
		delete_sprite(sprite, mlx);
		return (NULL);
	}
	mlx_delete_image(mlx, image);
	return (sprite);
}
