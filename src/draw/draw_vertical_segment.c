/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vertical_segment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:05:16 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/17 16:39:28 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*

**********CURRENT LINE HEIGHT**********

line height to draw = HEIGHT / ray[i].length;

starting point for the line to draw = -lineheight / 2 + HEIGHT / 2;

if (starting point < 0)
	starting point = 0;

end point for the line to draw = line height / 2 + HEIGHT / 2;

if (end point >= HEIGHT)
	end point = HEIGHT - 1;

if all else fails, try this:

lineheight = (128 * HEIGHT) / ray[x_pixel].distance;   <-- distance need to be fish eye corrected?!
if (lineheight > HEIGHT)
	lineheight = HEIGHT;

line offset = HEIGHT / 2 - lineheight / 2;

fisheye correction = player.angle - ray[x_pixel].angle;
if (correction < 0)
	correction += 2 * M_PI;
if (correction > 2 * M_PI)
	correction -= 2 * M_PI;

true distance = ray[x_pixel].distance * cos(correction);

***************************************

(portion) x pixel coordinate / 20 (nbr of 20x20 squares in real map) = gives number of square we're currently in (save as double)

double text_x pos = 1 - (round_up_portion - portion);

int text_x coord = text_x pos * 128; (round up/down)

***************************************

offset to determine correct column in texture:

for vertical grid boundaries: offset = ray.end_y % (texture size);
for horizontal grid boundaries: offset = ray.end_x % (texture size);

add fisheye effect protection to drawing:
- true length (if not already calculated for the struct) = abs(cos(angle)) * length

***************************************

texture step = 128 / lineheight;

texture starting point in bigger while loop: text_y = text_offset * text_step;

texture x-coordinate = (cub3D->rays[x_pixel].distance_x / 2) % 128;

*/


static void	draw_texture(t_cub3D *cub3D, int x, int start_y, int lineheight)
{
	float		tx_step;
	float		tx_draw_pos;
	int			tx_y;
	int			y_pixel;
	uint32_t	*color;

	tx_step = cub3D->rays[x].hit_texture->height / lineheight;
	tx_draw_pos = (start_y - HEIGHT / 2 + lineheight / 2) * tx_step;
	y_pixel = start_y;
	while (y_pixel < start_y + lineheight)
	{
		tx_y = (int)tx_draw_pos & (cub3D->rays[x].hit_texture->height - 1);
		tx_draw_pos += tx_step;
		color = (uint32_t *)get_pixels(cub3D->rays[x].hit_texture, cub3D->rays[x].hit_texture_pos_x, tx_y);
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

