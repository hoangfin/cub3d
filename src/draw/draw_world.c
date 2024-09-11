/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:17:11 by emansoor          #+#    #+#             */
/*   Updated: 2024/09/10 13:02:42 by emansoor         ###   ########.fr       */
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

/*
int	find_text_coordinate(t_ray ray)
{
	double	portion;
	int		rounded;

	portion = ray.x[1] / 20;
	rounded = portion; //automatically rounds double type down?
	return (128 * (portion - rounded)); //(rounds down automatically?)
}
*/

// east == red | north == green | west == yellow | south == blue
uint32_t	choose_color(t_ray ray) // this doesn't work properly yet
{
	if ((0 <= ray.angle && ray.angle < M_PI / 4) || (M_PI * 7/4 <= ray.angle && ray.angle < 2 * M_PI)) // red
	{
		if (ray.side == 0 && ray.angle < 2 * M_PI)
			return (color(255, 255, 0, 255));
		else if (ray.side == 0 && 0 <= ray.angle)
			return (color(0, 128, 0, 255));
		return (color(255, 0, 0, 255));
	}
	else if (M_PI / 4 <= ray.angle && ray.angle < (M_PI * 3)/4) // green
	{
		if (ray.side == 1 && ray.angle >= M_PI / 2)
			return (color(255, 255, 0, 255));
		else if (ray.side == 1 && ray.angle < M_PI / 2)
			return (color(255, 0, 0, 255));
		return (color(0, 128, 0, 255));
	}
	else if ((M_PI * 3)/4 <= ray.angle && ray.angle < (5 * M_PI)/4) // yellow
	{
		if (ray.side == 0 && ray.angle < M_PI)
			return (color(0, 0, 255, 255));
		else if (ray.side == 0 && ray.angle >= M_PI)
			return (color(0, 128, 0, 255));
		return (color(255, 255, 0, 255));
	}
	else if ((5 * M_PI)/4 <= ray.angle && ray.angle < M_PI * 7/4)
	{
		if (ray.side == 1 && ray.angle < 3 * M_PI / 2)
			return (color(255, 0, 0, 255));
		else if (ray.side == 1 && ray.angle >= 3 * M_PI / 2)
			return (color(255, 255, 0, 255));
		return (color(0, 0, 255, 255));
	}
	return (color(0, 0, 0, 255));	
}

static void	update_wall_slice(t_cub3D *cub3D, int start_y, int lineheight, int x_pixel)
{
	int		index_y;

	index_y = 0;
	while (index_y < start_y)
	{
		mlx_put_pixel(cub3D->image.world, x_pixel, index_y, cub3D->map->color_ceiling);
		index_y++;
	}
	while (start_y < index_y + lineheight)
	{
		mlx_put_pixel(cub3D->image.world, x_pixel, start_y, choose_color(cub3D->rays[x_pixel]));
		start_y++;
	}
	while (start_y < HEIGHT)
	{
		mlx_put_pixel(cub3D->image.world, x_pixel, start_y, cub3D->map->color_floor);
		start_y++;
	}
}

void	draw_world(t_cub3D *cub3D)
{
	int		x_pixel;
	int		lineheight;
	int		start_y;
	double	hitangle;
	double	hitdist;
	double	text_offset;

	x_pixel = 0;
	while (x_pixel < WIDTH)
	{
		hitangle = cub3D->player.angle - cub3D->rays[x_pixel].angle;
		if (hitangle < 0)
			hitangle += 2 * M_PI;
		if (hitangle > 2 * M_PI)
			hitangle -= 2 * M_PI;
		hitdist = cub3D->rays[x_pixel].distance * cos(hitangle) * (MAP_CELL_SIZE / 2);
		if (hitdist < 1)
			hitdist = 1.0;
		lineheight = (128 * HEIGHT) / hitdist;
		//printf("lineheight: %d\n", lineheight);
		text_offset = 0;
		if (lineheight > HEIGHT)
		{
			text_offset = (lineheight - HEIGHT) / 2;
			lineheight = HEIGHT;
		}
		(void)text_offset;
		start_y = HEIGHT / 2 - lineheight / 2;
		update_wall_slice(cub3D, start_y, lineheight, x_pixel);
		x_pixel++;
	}
}

/* static void	draw_wall_slice(t_cub3D *cub3D, int start_y, int end_y, int x_pixel)
{
	//double	step;
	//double	textpos;
	//int		lineheight;

	//lineheight = end_y - start_y;
	//step = 1.0 * 128 * lineheight; // verify this
	//textpos = (start_y - HEIGHT / 2 + lineheight / 2) * step;
	while (start_y < end_y)
	{
		mlx_put_pixel(\
			cub3D->image.world,
			x_pixel,
			start_y,
			choose_color(cub3D->rays[x_pixel])\
			);
			//get_pixels(cub3D->map->wall_paths[choose_texture(cub3D->rays[x_pixel])], find_text_coordinate(cub3D->rays[x_pixel]), textpos));
		//textpos++;
		start_y++;
	}
}*/
