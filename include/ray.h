/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:41:46 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/26 13:12:46 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include "MLX42.h"

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
	int32_t		hit_row;
	int32_t		hit_col;
	int32_t		hit_side;
	mlx_image_t	*hit_texture;
	int32_t		hit_texture_pos_x;
}	t_ray;

void	init_ray(t_ray *ray, int32_t x, int32_t y, double angle);

#endif
