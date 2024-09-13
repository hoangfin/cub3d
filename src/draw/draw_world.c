/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:17:11 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/13 12:16:17 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

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


// east == red | north == green | west == yellow | south == blue
uint32_t	choose_color(t_ray ray)
{
	if ((ray.angle < M_PI / 4) || ((M_PI * 7) / 4 <= ray.angle)) // red
	{
		if (ray.side == 0 && ray.angle < 2 * M_PI)
			return (color(255, 255, 0, 255)); // yellow
		else if (ray.side == 0 && 0 <= ray.angle)
			return (color(0, 128, 0, 255)); // green
		return (color(255, 0, 0, 255));
	}
	else if (M_PI / 4 <= ray.angle && ray.angle < (M_PI * 3) / 4) // green
	{
		if (ray.side == 1 && ray.angle >= M_PI / 2)
			return (color(255, 255, 0, 255)); // yellow
		else if (ray.side == 1 && ray.angle < M_PI / 2)
			return (color(255, 0, 0, 255)); // red
		return (color(0, 128, 0, 255));
	}
	else if ((M_PI * 3) / 4 <= ray.angle && ray.angle < (5 * M_PI) / 4) // yellow
	{
		if (ray.side == 0 && ray.angle < M_PI)
			return (color(0, 0, 255, 255)); // blue
		else if (ray.side == 0 && ray.angle >= M_PI)
			return (color(0, 128, 0, 255)); // green
		return (color(255, 255, 0, 255));
	}
	else if ((5 * M_PI) / 4 <= ray.angle && ray.angle < (M_PI * 7) / 4) // blue
	{
		if (ray.side == 1 && ray.angle < 3 * M_PI / 2)
			return (color(255, 0, 0, 255)); // red
		else if (ray.side == 1 && ray.angle >= 3 * M_PI / 2)
			return (color(255, 255, 0, 255)); // yellow
		return (color(0, 0, 255, 255));
	}
	return (color(0, 0, 0, 255));
}


int	texture_position(t_ray ray, mlx_image_t *texture)
{
	double	hitpoint_x;
	int		tx_coordinate;

	hitpoint_x = ray.x_end;
	hitpoint_x -= floor(hitpoint_x);
	tx_coordinate = (int)(hitpoint_x * (double)texture->width);
	tx_coordinate = texture->width - tx_coordinate - 1;
	return (tx_coordinate);
}


int	choose_texture(t_ray ray)
{
	/* if ((ray.angle < M_PI / 4) || ((M_PI * 7) / 4 <= ray.angle)) // ray looks right
	{
		if (ray.side == 0 && ray.angle < 2 * M_PI) // ray looks down, return north texture
			return (0);
		else if (ray.side == 0 && 0 <= ray.angle) // ray looks up, return south texture
			return (2);
		return (3); // ray looking straight right, return west texture
	}
	else if (M_PI / 4 <= ray.angle && ray.angle < (M_PI * 3) / 4) // ray looks up
	{
		if (ray.side == 1 && ray.angle >= M_PI / 2) // ray looks left, return east texture
			return (1);
		else if (ray.side == 1 && ray.angle < M_PI / 2) // ray looks right, return west texture
			return (3);
		return (2); // ray looking straight up, return south texture
	}
	else if ((M_PI * 3) / 4 <= ray.angle && ray.angle < (5 * M_PI) / 4) // ray looks left
	{
		if (ray.side == 0 && ray.angle < M_PI) // ray looks up, return south texture
			return (2);
		else if (ray.side == 0 && ray.angle >= M_PI) // ray looks down, return north texture
			return (0);
		return (1); // ray looks straight left, return east texture
	}
	else if ((5 * M_PI) / 4 <= ray.angle && ray.angle < (M_PI * 7) / 4) // ray looks down
	{
		if (ray.side == 1 && ray.angle < 3 * M_PI / 2) // ray looks left, return east texture
			return (1);
		else if (ray.side == 1 && ray.angle >= 3 * M_PI / 2) // ray looks right, return west texture
			return (3);
		return (0); // ray looks straight down, return north texture
	} */
	(void)ray;
	return (2);
}


static int	draw_texture(t_cub3D *cub3D, int x, int start_y, int lineheight)
{
	float		tx_step;
	float		tx_draw_pos;
	int			tx_y;
	int			tx_x;
	int			y_pixel;
	uint32_t	*color;
	mlx_image_t	*texture;

	texture = cub3D->asset.walls[choose_texture(cub3D->rays[x])];
	tx_step = texture->height / lineheight;
	tx_draw_pos = (start_y - HEIGHT / 2 + lineheight / 2) * tx_step;
	tx_x = texture_position(cub3D->rays[x], texture);
	y_pixel = start_y;
	//printf("step: %f\n", tx_step);
	while (y_pixel < start_y + lineheight)
	{
		tx_y = (int)tx_draw_pos & (texture->height - 1);
		tx_draw_pos += tx_step;
		//printf("pixel coordinates in texture: x = %d | y = %d\n", tx_x, tx_y);
		color = (uint32_t *)get_pixels(texture, tx_x, tx_y);
		mlx_put_pixel(cub3D->image.world, x, y_pixel, *color);
		y_pixel++;
	}
	return (y_pixel);
}

static int	draw_ceiling(t_cub3D *cub3D, int y_start, int y_end, int x)
{
	while (y_start < y_end)
	{
		mlx_put_pixel(cub3D->image.world, x, y_start, cub3D->map->color_ceiling);
		y_start++;
	}
	return (y_start);
}

static void	draw_floor(t_cub3D *cub3D, int y_start, int y_end, int x)
{
	while (y_start < y_end)
	{
		mlx_put_pixel(cub3D->image.world, x, y_start, cub3D->map->color_floor);
		y_start++;
	}
}

static void	update_wall_slice(t_cub3D *cub3D, int start_y, int lineheight, int x)
{
	int	y_pixel;
	
	y_pixel = draw_ceiling(cub3D, 0, start_y, x);
	y_pixel = draw_texture(cub3D, x, start_y, lineheight);
	draw_floor(cub3D, y_pixel, HEIGHT, x);
}

void	draw_world(t_cub3D *cub3D)
{
	int			x;
	int			start_y;
	int			lineheight;
	double		hitangle;
	double		hitdist;
	mlx_image_t	*texture;

	x = 0;
	while (x < WIDTH)
	{
		hitangle = cub3D->player.angle - cub3D->rays[x].angle;
		if (hitangle < 0)
			hitangle += 2 * M_PI;
		if (hitangle > 2 * M_PI)
			hitangle -= 2 * M_PI;
		hitdist = cub3D->rays[x].distance * cos(hitangle) * (MAP_CELL_SIZE / 4);
		if (hitdist < 1)
			hitdist = 1.0;
		texture = cub3D->asset.walls[choose_texture(cub3D->rays[x])];
		lineheight = (texture->height * HEIGHT) / hitdist;
		if (lineheight > HEIGHT)
			lineheight = HEIGHT;
		start_y = HEIGHT / 2 - lineheight / 2;
		update_wall_slice(cub3D, start_y, lineheight, x);
		x++;
	}
}

