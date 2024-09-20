/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:15:15 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 22:17:09 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

typedef struct s_sprite
{
	mlx_image_t	***frames;
	int32_t		frame_index;
	uint32_t	frame_w;
	uint32_t	frame_h;
	uint32_t	row_count;
	uint32_t	col_count;
}	t_sprite;

void		delete_sprite(t_sprite *sprite, mlx_t *mlx);
t_sprite	*image_to_sprite(
				mlx_t *mlx,
				mlx_image_t *image,
				uint32_t row_count,
				uint32_t col_count
);
