/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:41:46 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/20 13:41:57 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

typedef struct s_ray
{
	double		x_start;
	double		x_end;
	double		y_start;
	double		y_end;
	double		distance;
	double		angle;
	double		dir_x;
	double		dir_y;
	int32_t		hit_side;
	mlx_image_t	*hit_texture;
	int32_t		hit_texture_pos_x;
}	t_ray;
