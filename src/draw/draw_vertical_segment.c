/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_segment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:05:16 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/18 14:58:40 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_texture(t_cub3D *cub3D, int x, int start_y, int lineheight)
{
	double		scale;
	double		texture_y;
	int32_t		hit_texture_pos_y;
	int			y_pixel;
	uint32_t	*color;

	scale = (double)cub3D->rays[x].hit_texture->height / (double)lineheight;
	texture_y = (start_y - HEIGHT / 2 + lineheight / 2) * scale;
	y_pixel = start_y;
	while (y_pixel < start_y + lineheight)
	{
		hit_texture_pos_y = (int32_t)texture_y & (cub3D->rays[x].hit_texture->height - 1);
		texture_y += scale;
		color = (uint32_t *)get_pixels(cub3D->rays[x].hit_texture, cub3D->rays[x].hit_texture_pos_x, hit_texture_pos_y);
		mlx_put_pixel(cub3D->image.scene, x, y_pixel, *color);
		y_pixel++;
	}
}

static void	draw_ceiling(t_cub3D *cub3D, int y_start, int y_end, int x)
{
	while (y_start < y_end)
	{
		mlx_put_pixel(cub3D->image.scene, x, y_start, cub3D->map->color_ceiling);
		y_start++;
	}
}

static void	draw_floor(t_cub3D *cub3D, int y_start, int y_end, int x)
{
	while (y_start < y_end)
	{
		mlx_put_pixel(cub3D->image.scene, x, y_start, cub3D->map->color_floor);
		y_start++;
	}
}

void	draw_vertical_segment(t_cub3D *cub3D, int start_y, int lineheight, int x)
{
	draw_ceiling(cub3D, 0, start_y, x);
	draw_texture(cub3D, x, start_y, lineheight);
	draw_floor(cub3D, start_y + lineheight, HEIGHT, x);
}

