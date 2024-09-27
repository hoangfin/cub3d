/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:29:43 by hoatran           #+#    #+#             */
/*   Updated: 2024/09/27 14:00:48 by emansoor         ###   ########.fr       */
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

	if ((uint32_t)hit_texture_pos_y < cub3D->rays[x].hit_texture->height - 1)
	{
		dest_pixels = (uint32_t *)get_pixels(cub3D->image.scene, x, y_pixel);
		src_pixels = (uint32_t *)get_pixels(cub3D->rays[x].hit_texture,
				cub3D->rays[x].hit_texture_pos_x,
				hit_texture_pos_y);
		*dest_pixels = *src_pixels;
	}
	else
	{
		dest_pixels = (uint32_t *)get_pixels(cub3D->image.scene, x, y_pixel);
		src_pixels = (uint32_t *)get_pixels(cub3D->rays[x].hit_texture,
				cub3D->rays[x].hit_texture_pos_x,
				cub3D->rays[x].hit_texture->height - 1);
		*dest_pixels = *src_pixels;
	}
}

static void	draw_texture(t_cub3D *cub3d, int32_t i, double wall_height,
double scale)
{
	double		texture_y;
	int32_t		hit_texture_pos_y;
	int32_t		start_y;
	double		texture_offset;

	texture_offset = 0;
	if (wall_height >= HEIGHT)
	{
		texture_offset = (wall_height - HEIGHT) / -1.0;
		wall_height = HEIGHT - 1;
	}
	start_y = HEIGHT / 2 - wall_height / 2;
	texture_y = (start_y - HEIGHT / 2 + wall_height / 2) * scale
		* texture_offset;
	while (wall_height > 0)
	{
		hit_texture_pos_y = (int32_t)texture_y;
		texture_y += scale;
		copy_pixel(cub3d, i, start_y, hit_texture_pos_y);
		start_y++;
		wall_height--;
	}
}

void	draw_scene(t_cub3D *cub3d)
{
	int32_t	i;
	double	wall_height;
	double	scale;
	double	camera_plane_dist;

	i = 0;
	camera_plane_dist = (WIDTH / 2) / tan(M_PI / 6);
	clear_image(cub3d->image.scene);
	while (i < WIDTH)
	{
		wall_height = (MAP_CELL_SIZE / cub3d->rays[i].distance)
			* camera_plane_dist;
		scale = (double)cub3d->rays[i].hit_texture->height / wall_height;
		draw_texture(cub3d, i, wall_height, scale);
		i++;
	}
}
