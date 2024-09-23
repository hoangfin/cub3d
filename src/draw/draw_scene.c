/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:29:43 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/23 21:19:05 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	copy_pixel(
	t_cub3D *cub3D,
	int32_t x,
	int32_t y_pixel,
	int32_t hit_texture_pos_y
)
{
	uint32_t	*dest_pixels;
	uint32_t	*src_pixels;

	dest_pixels = (uint32_t *)get_pixels(cub3D->image.scene, x, y_pixel);
	src_pixels = (uint32_t *)get_pixels(cub3D->rays[x].hit_texture,
			cub3D->rays[x].hit_texture_pos_x, hit_texture_pos_y);
	*dest_pixels = *src_pixels;
}

void	draw_texture(t_cub3D *cub3D, int x, int start_y, int lineheight)
{
	double		scale;
	double		texture_y;
	int32_t		hit_texture_pos_y;
	int32_t		y_pixel;

	scale = (double)cub3D->rays[x].hit_texture->height / (double)lineheight;
	texture_y = (start_y - HEIGHT / 2 + lineheight / 2) * scale;
	y_pixel = start_y;
	while (y_pixel < start_y + lineheight)
	{
		hit_texture_pos_y = (int32_t)texture_y
			& (cub3D->rays[x].hit_texture->height - 1);
		texture_y += scale;
		copy_pixel(cub3D, x, y_pixel, hit_texture_pos_y);
		y_pixel++;
	}
}

void	draw_scene(t_cub3D *cub3d)
{
	const double	camera_plane_distance = (WIDTH / 2) / tan(M_PI / 6);
	int32_t			i;
	double			wall_height;

	i = 0;
	clear_image(cub3d->image.scene);
	while (i < WIDTH)
	{
		wall_height = (10 / cub3d->rays[i].distance) * camera_plane_distance;
		if (wall_height >= HEIGHT)
			wall_height = HEIGHT - 1;
        draw_texture(cub3d, i, HEIGHT / 2 - wall_height / 2, wall_height);
		i++;
	}
	copy_pixels(cub3d->image.scene, cub3d->doors[0].image, cub3d->doors[0].image->width, cub3d->doors[0].image->height);
}
