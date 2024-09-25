/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:20:15 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/25 21:30:49 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
# define UTILITY_H

# include <math.h>
# include "MLX42.h"

void		clear_image(mlx_image_t *image);
void		fill(mlx_image_t *image, uint32_t color);
uint32_t	color(int32_t r, int32_t g, int32_t b, int32_t a);
int32_t		max(int32_t a, int32_t b);
uint8_t		*get_pixels(mlx_image_t *image, int32_t x, int32_t y);
bool		is_equal(double a, double b);
mlx_image_t	*load_png(mlx_t *mlx, const char *pathname);

void		copy_pixels(
				mlx_image_t *dest,
				mlx_image_t *src,
				int32_t offset_x,
				int32_t offset_y
			);

void		clear_pixels(
				uint8_t *start,
				uint32_t image_width,
				int32_t offset_x,
				int32_t offset_y
			);

#endif
