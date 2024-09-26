/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:15:15 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 15:11:36 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "MLX42.h"

typedef struct s_sprite
{
	mlx_image_t	***frames;
	uint32_t	frame_w;
	uint32_t	frame_h;
	uint32_t	row_count;
	uint32_t	col_count;
}	t_sprite;

#endif
